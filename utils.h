#pragma once
#include "pch.h"
#include "types.h"
#include "structs.h"

// extensions & layers 
bool check_supported_extensions_by_vk_instance(cstr **ext_name_list, u32 ext_cnt);

void print_supported_extensions_by_instance();

bool check_supported_layers_by_instance(cstr **layer_name_list, u32 layer_cnt);

void print_supported_layer_by_instance();

std::vector<cstr *> get_required_extensions(bool use_debug);

std::vector<cstr *> get_required_layers(bool use_debug);

// devices 
bool check_suitable_physical_device(VkPhysicalDevice device, VkSurfaceKHR surface);

QueueFamilyIndices find_queue_family_indices(VkPhysicalDevice device);

QueueFamilyIndices find_queue_family_indices(VkPhysicalDevice device, VkSurfaceKHR surface);

bool check_supported_extensions_by_vk_device(VkPhysicalDevice device);

std::vector<cstr*> get_required_device_extensions();

// swapchain
SwapChainSupportDetails query_swapchain_support(VkPhysicalDevice device, VkSurfaceKHR surface);

VkSurfaceFormatKHR choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR>& available_formats);

VkPresentModeKHR choose_swap_present_mode(const std::vector<VkPresentModeKHR>& available_present_modes);

VkExtent2D choose_swap_extent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window);

VkDebugUtilsMessengerCreateInfoEXT make_debug_messenger_create_info();

VkResult create_debug_utils_messenger_ext(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *info, const VkAllocationCallbacks *allocator, VkDebugUtilsMessengerEXT *debug_messenger);

void destroy_debug_utils_messenger_ext(VkInstance instance, VkDebugUtilsMessengerEXT debug_messenger, const VkAllocationCallbacks *allocator);