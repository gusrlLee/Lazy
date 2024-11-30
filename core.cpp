#include "core.h"
#include "log.h"
#include "utils.h"

CoreInfo &CoreInfo::set_validation_layer(bool v)
{
    is_use_validation_layer = v;
    return *this;
}

CoreInfo &CoreInfo::set_win_ptr(GLFWwindow *win_ptr)
{
    this->win_ptr = win_ptr;
    return *this;
}

void Core::init_core(CoreInfo &info)
{
    m_is_ready = false;
    m_info = info;

    create_instance();
    create_surface();
    create_physical_device();
    create_device();
    create_swapchain();
    create_image_views();

    m_is_ready = true;
}

void Core::reset()
{
    for (auto image_view : m_vk_swapchain_image_views)
    {
        vkDestroyImageView(m_vk_device, image_view, nullptr);
    }

    vkDestroySwapchainKHR(m_vk_device, m_vk_swapchain, nullptr);
    // device
    vkDestroyDevice(m_vk_device, nullptr);

    // debug messenger
    if (m_info.is_use_validation_layer)
    {
        destroy_debug_utils_messenger_ext(m_vk_inst, m_vk_debug_util, nullptr);
    }

    // suface
    vkDestroySurfaceKHR(m_vk_inst, m_vk_surface, nullptr);

    // instance
    vkDestroyInstance(m_vk_inst, nullptr);
}

void Core::create_instance()
{
    LOG("Create vulkan instance.. ");
    VkApplicationInfo app_info{};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = "Engine App";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "Engine Core";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo inst_info{};
    inst_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    inst_info.pApplicationInfo = &app_info;
#if __APPLE__
    inst_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif

    if (m_info.is_use_validation_layer)
    {
        print_supported_extensions_by_instance();
        print_supported_layer_by_instance();
    }

    std::vector<cstr *> extensions_list = get_required_extensions(m_info.is_use_validation_layer);
    std::vector<cstr *> layer_list = get_required_layers(m_info.is_use_validation_layer);

    if (!check_supported_extensions_by_vk_instance(extensions_list.data(), extensions_list.size()))
    {
        FATAL("Failed to support extensions...");
    }

    if (!check_supported_layers_by_instance(layer_list.data(), layer_list.size()))
    {
        FATAL("Failed to support layers...");
    }

    inst_info.enabledExtensionCount = static_cast<u32>(extensions_list.size());
    inst_info.ppEnabledExtensionNames = extensions_list.data();
    inst_info.enabledLayerCount = static_cast<u32>(layer_list.size());
    inst_info.ppEnabledLayerNames = layer_list.data();

    VkDebugUtilsMessengerCreateInfoEXT debug_info = make_debug_messenger_create_info();
    if (m_info.is_use_validation_layer)
    {
        inst_info.pNext = (VkDebugUtilsMessengerCreateInfoEXT *)&debug_info;
    }

    CHECK(vkCreateInstance(&inst_info, nullptr, &m_vk_inst));
    if (m_info.is_use_validation_layer)
    {
        CHECK(create_debug_utils_messenger_ext(m_vk_inst, &debug_info, nullptr, &m_vk_debug_util));
    }
}

void Core::create_surface()
{
    CHECK(glfwCreateWindowSurface(m_vk_inst, m_info.win_ptr, nullptr, &m_vk_surface));
}

void Core::create_physical_device()
{
    u32 device_cnt = 0;
    vkEnumeratePhysicalDevices(m_vk_inst, &device_cnt, nullptr);
    if (device_cnt == 0)
    {
        FATAL("Failed to find GPUs with vulkan supported!... :-(");
    }

    std::vector<VkPhysicalDevice> devices(device_cnt);
    vkEnumeratePhysicalDevices(m_vk_inst, &device_cnt, devices.data());

    for (const auto &device : devices)
    {
        if (check_suitable_physical_device(device, m_vk_surface))
        {
            m_vk_mounted_gpu = device;
            break;
        }
    }

    if (m_vk_mounted_gpu == VK_NULL_HANDLE)
    {
        FATAL("Failed to find a suitable physical device.. :-(");
    }
}

void Core::create_device()
{
    // queue
    QueueFamilyIndices indices = find_queue_family_indices(m_vk_mounted_gpu, m_vk_surface);

    std::vector<VkDeviceQueueCreateInfo> qinfos;
    std::set<u32> unique_queue_indices = {indices.graphics_family.value(), indices.present_family.value()};
    f32 queue_priority = 1.0f;

    for (u32 queue_index : unique_queue_indices)
    {
        VkDeviceQueueCreateInfo qinfo{
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .queueFamilyIndex = queue_index,
            .queueCount = 1,
            .pQueuePriorities = &queue_priority};

        qinfos.push_back(qinfo);
    }

    // device
    VkPhysicalDeviceFeatures device_basic_features{};
    VkDeviceCreateInfo dinfo{};

    dinfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    dinfo.queueCreateInfoCount = static_cast<u32>(qinfos.size());
    dinfo.pQueueCreateInfos = qinfos.data();
    dinfo.pEnabledFeatures = &device_basic_features;

    std::vector<cstr *> device_extensions = get_required_device_extensions();
    dinfo.enabledExtensionCount = static_cast<u32>(device_extensions.size());
    dinfo.ppEnabledExtensionNames = device_extensions.data();

    std::vector<cstr *> layer_list = get_required_layers(m_info.is_use_validation_layer);
    if (m_info.is_use_validation_layer)
    {
        dinfo.enabledLayerCount = static_cast<u32>(layer_list.size());
        dinfo.ppEnabledLayerNames = layer_list.data();
    }
    else
    {
        dinfo.enabledLayerCount = 0;
    }

    CHECK(vkCreateDevice(m_vk_mounted_gpu, &dinfo, nullptr, &m_vk_device));

    // get queues
    vkGetDeviceQueue(m_vk_device, indices.graphics_family.value(), 0, &m_vk_graphics_queue);
    vkGetDeviceQueue(m_vk_device, indices.present_family.value(), 0, &m_vk_present_queue);
}

void Core::create_swapchain()
{
    LOG("Create vulkan swapchain.. ");
    SwapChainSupportDetails swapchain_support = query_swapchain_support(m_vk_mounted_gpu, m_vk_surface);

    VkSurfaceFormatKHR surface_format = choose_swap_surface_format(swapchain_support.formats);
    VkPresentModeKHR present_mode = choose_swap_present_mode(swapchain_support.present_modes);
    VkExtent2D extent = choose_swap_extent(swapchain_support.capabilities, m_info.win_ptr);

    u32 image_cnt = swapchain_support.capabilities.minImageCount + 1;
    if (swapchain_support.capabilities.maxImageCount > 0 && image_cnt > swapchain_support.capabilities.maxImageCount)
    {
        image_cnt = swapchain_support.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR sinfo{};
    sinfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    sinfo.surface = m_vk_surface;
    sinfo.minImageCount = image_cnt;
    sinfo.imageFormat = surface_format.format;
    sinfo.imageColorSpace = surface_format.colorSpace;
    sinfo.imageExtent = extent;
    sinfo.imageArrayLayers = 1;
    sinfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices indices = find_queue_family_indices(m_vk_mounted_gpu, m_vk_surface);
    u32 queue_family_indices[] = {
        indices.graphics_family.value(),
        indices.present_family.value()};

    if (indices.graphics_family != indices.present_family)
    {
        sinfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        sinfo.queueFamilyIndexCount = 2;
        sinfo.pQueueFamilyIndices = queue_family_indices;
    }
    else
    {
        sinfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        sinfo.queueFamilyIndexCount = 0;
        sinfo.pQueueFamilyIndices = nullptr;
    }

    sinfo.preTransform = swapchain_support.capabilities.currentTransform;
    sinfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    sinfo.presentMode = present_mode;
    sinfo.clipped = VK_TRUE;
    sinfo.oldSwapchain = VK_NULL_HANDLE;

    CHECK(vkCreateSwapchainKHR(m_vk_device, &sinfo, nullptr, &m_vk_swapchain));

    // setting
    vkGetSwapchainImagesKHR(m_vk_device, m_vk_swapchain, &image_cnt, nullptr);
    m_vk_swapchain_images.resize(image_cnt);
    vkGetSwapchainImagesKHR(m_vk_device, m_vk_swapchain, &image_cnt, m_vk_swapchain_images.data());

    m_vk_swapchain_image_format = surface_format.format;
    m_vk_swapchain_extent = extent;
}

void Core::create_image_views()
{
    m_vk_swapchain_image_views.resize(m_vk_swapchain_images.size());
    for (size i = 0; i < m_vk_swapchain_image_views.size(); i++)
    {
        VkImageViewCreateInfo iinfo{};
        iinfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        iinfo.image = m_vk_swapchain_images[i];
        iinfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        iinfo.format = m_vk_swapchain_image_format;
        iinfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        iinfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        iinfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        iinfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

        iinfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        iinfo.subresourceRange.baseMipLevel = 0;
        iinfo.subresourceRange.levelCount = 1;
        iinfo.subresourceRange.baseArrayLayer = 0;
        iinfo.subresourceRange.layerCount = 1;

        CHECK(vkCreateImageView(m_vk_device, &iinfo, nullptr, &m_vk_swapchain_image_views[i]));
    }
}