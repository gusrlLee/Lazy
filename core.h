#pragma once
#include "pch.h"
#include "types.h"

struct CoreInfo
{
    GLFWwindow* win_ptr;
    bool is_use_validation_layer;

    CoreInfo& set_win_ptr(GLFWwindow* win_ptr);
    CoreInfo& set_validation_layer(bool v);
};

class Core
{
public:
    void init_core(CoreInfo &info);
    void reset();

private:
    void create_instance();
    void create_swapchain();

    bool m_is_ready = false;
    GLFWwindow* m_win_ptr;
    CoreInfo m_info;

    // TODO: Vulkan initialization
    VkInstance m_vk_inst;
    VkDebugUtilsMessengerEXT m_vk_debug_util;
};