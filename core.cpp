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
    win_ptr = win_ptr;
    return *this;
}

void Core::init_core(CoreInfo &info)
{
    m_is_ready = false;
    m_info = info;

    create_instance();
    create_swapchain();

    m_is_ready = true;
}

void Core::reset()
{
    // debug messenger
    if (m_info.is_use_validation_layer)
    {
        destroy_debug_utils_messenger_ext(m_vk_inst, m_vk_debug_util, nullptr);
    }

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

void Core::create_swapchain()
{
    LOG("Create vulkan swapchain.. ");
}