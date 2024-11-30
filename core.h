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
    // initializaiton required functions
    void create_instance();
    void create_physical_device();
    void create_device();
    void create_surface();
    void create_swapchain();

    bool m_is_ready = false;
    GLFWwindow *m_win_ptr;
    CoreInfo m_info;

    // vk : Instance 
    VkInstance m_vk_inst;
    VkDebugUtilsMessengerEXT m_vk_debug_util;

    // vk : Device 
    VkPhysicalDevice m_vk_mounted_gpu = VK_NULL_HANDLE;
    VkDevice m_vk_device;

    // vk : Qeueus
    VkQueue m_vk_graphics_queue;
    VkQueue m_vk_present_queue;

    // vk : Surface 
    VkSurfaceKHR m_vk_surface;

    VkSwapchainKHR m_vk_swapchain;
};