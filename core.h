#pragma once
#include "pch.h"
#include "types.h"

struct CoreInfo
{
    GLFWwindow *win_ptr;
    bool is_use_validation_layer;

    CoreInfo &set_win_ptr(GLFWwindow *win_ptr);
    CoreInfo &set_validation_layer(bool v);
};

class Core
{
public:
    void init_core(CoreInfo &info);
    void reset();

private:
    void create_instance();
    void create_physical_device();
    void create_swapchain();

    bool m_is_ready = false;
    GLFWwindow *m_win_ptr;
    CoreInfo m_info;

    // TODO: Vulkan initialization
    VkInstance m_vk_inst;
    VkDebugUtilsMessengerEXT m_vk_debug_util;
    VkPhysicalDevice m_vk_mounted_gpu = VK_NULL_HANDLE;
};

/*
    void pickPhysicalDevice() {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

        if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        for (const auto& device : devices) {
            if (isDeviceSuitable(device)) {
                physicalDevice = device;
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("failed to find a suitable GPU!");
        }
    }

    bool isDeviceSuitable(VkPhysicalDevice device) {
        QueueFamilyIndices indices = findQueueFamilies(device);

        return indices.isComplete();
    }

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamily = i;
            }

            if (indices.isComplete()) {
                break;
            }

            i++;
        }

        return indices;
    }
    */