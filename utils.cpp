#include "utils.h"
#include "log.h"

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
    void *pUserData)
{

    std::cerr << "[VALIDATION LAYER]: " << pCallbackData->pMessage << '\n';
    return VK_FALSE;
}

bool check_supported_extensions_by_vk_instance(cstr **ext_name_list, u32 ext_cnt)
{
    u32 supported_ext_cnt = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &supported_ext_cnt, nullptr);
    std::vector<VkExtensionProperties> supported_ext_list(supported_ext_cnt);
    vkEnumerateInstanceExtensionProperties(nullptr, &supported_ext_cnt, supported_ext_list.data());

    bool is_found = false;
    for (i32 i = 0; i < ext_cnt; i++)
    {
        cstr *ext_name = ext_name_list[i];
        is_found = false;

        for (VkExtensionProperties supported_ext : supported_ext_list)
        {
            if (strcmp(ext_name, supported_ext.extensionName) == 0)
            {
                is_found = true;
                break;
            }
        }
        if (!is_found)
        {
            return false;
        }
    }

    return true;
}

void print_supported_extensions_by_instance()
{
    u32 supported_ext_cnt = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &supported_ext_cnt, nullptr);
    std::vector<VkExtensionProperties> supported_ext_list(supported_ext_cnt);
    vkEnumerateInstanceExtensionProperties(nullptr, &supported_ext_cnt, supported_ext_list.data());
    LOG("Supported extensions list ================================================ ");
    for (VkExtensionProperties supported_ext : supported_ext_list)
    {
        LOG(supported_ext.extensionName);
    }
}

bool check_supported_layers_by_instance(cstr **layer_name_list, u32 layer_cnt)
{
    u32 supported_layer_cnt = 0;
    vkEnumerateInstanceLayerProperties(&supported_layer_cnt, nullptr);
    std::vector<VkLayerProperties> supported_layer_list(supported_layer_cnt);
    vkEnumerateInstanceLayerProperties(&supported_layer_cnt, supported_layer_list.data());

    bool is_found = false;
    for (u32 i = 0; i < layer_cnt; i++)
    {
        cstr *layer_name = layer_name_list[i];
        is_found = false;

        for (VkLayerProperties supported_layer : supported_layer_list)
        {
            if (strcmp(layer_name, supported_layer.layerName) == 0)
            {
                is_found = true;
                break;
            }
        }
        if (!is_found)
        {
            return false;
        }
    }

    return true;
}

void print_supported_layer_by_instance()
{
    u32 supported_layer_cnt = 0;
    vkEnumerateInstanceLayerProperties(&supported_layer_cnt, nullptr);
    std::vector<VkLayerProperties> supported_layer_list(supported_layer_cnt);
    vkEnumerateInstanceLayerProperties(&supported_layer_cnt, supported_layer_list.data());
    LOG("Supported layer list ================================================ ");
    for (VkLayerProperties supported_layer : supported_layer_list)
    {
        LOG(supported_layer.layerName);
    }
}

std::vector<cstr *> get_required_extensions(bool use_debug)
{
    u32 extensions_cnt;
    cstr **extensions_list;

    extensions_list = glfwGetRequiredInstanceExtensions(&extensions_cnt);
    std::vector<cstr *> result(extensions_list, extensions_list + extensions_cnt);

    if (use_debug)
    {
        result.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

#if __APPLE__
    result.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif

    return result;
}

std::vector<cstr *> get_required_layers(bool use_debug)
{
    std::vector<cstr *> result;
    if (use_debug)
    {
        result.push_back("VK_LAYER_KHRONOS_validation");
    }
    return result;
}

bool check_suitable_physical_device(VkPhysicalDevice device, VkSurfaceKHR surface)
{
    QueueFamilyIndices indices = find_queue_family_indices(device, surface);
    return indices.is_complete();
}

QueueFamilyIndices find_queue_family_indices(VkPhysicalDevice device)
{
    QueueFamilyIndices indices;
    u32 queue_family_cnt = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_cnt, nullptr);
    std::vector<VkQueueFamilyProperties> queue_familes(queue_family_cnt);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_cnt, queue_familes.data());

    i32 i = 0;
    for (const auto &queue_family : queue_familes)
    {
        if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            indices.graphics_family = i;
        }

        if (indices.is_complete())
        {
            break;
        }
    }

    return indices;
}

QueueFamilyIndices find_queue_family_indices(VkPhysicalDevice device, VkSurfaceKHR surface)
{
    QueueFamilyIndices indices;
    u32 queue_family_cnt = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_cnt, nullptr);
    std::vector<VkQueueFamilyProperties> queue_familes(queue_family_cnt);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_cnt, queue_familes.data());

    i32 i = 0;

    for (const auto &queue_family : queue_familes)
    {
        if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            indices.graphics_family = i;
        }

        VkBool32 present_support = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &present_support);

        if (present_support)
        {
            indices.present_family = i;
        }

        if (indices.is_complete())
        {
            break;
        }
    }

    return indices;
}



VkDebugUtilsMessengerCreateInfoEXT make_debug_messenger_create_info()
{
    VkDebugUtilsMessengerCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    info.pfnUserCallback = debugCallback;
    info.pUserData = nullptr; // Optional
    return info;
}

VkResult create_debug_utils_messenger_ext(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *info, const VkAllocationCallbacks *allocator, VkDebugUtilsMessengerEXT *debug_messenger)
{
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr)
    {
        return func(instance, info, allocator, debug_messenger);
    }
    else
    {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void destroy_debug_utils_messenger_ext(VkInstance instance, VkDebugUtilsMessengerEXT debug_messenger, const VkAllocationCallbacks *allocator)
{
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr)
    {
        func(instance, debug_messenger, allocator);
    }
}