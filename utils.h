#pragma once
#include "pch.h"
#include "types.h"

bool check_supported_extensions_by_vk_instance(cstr **ext_name_list, u32 ext_cnt);

void print_supported_extensions_by_instance();

bool check_supported_layers_by_instance(cstr **layer_name_list, u32 layer_cnt);

void print_supported_layer_by_instance();

std::vector<cstr *> get_required_extensions(bool use_debug);

std::vector<cstr *> get_required_layers(bool use_debug);

VkDebugUtilsMessengerCreateInfoEXT make_debug_messenger_create_info();

VkResult create_debug_utils_messenger_ext(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *info, const VkAllocationCallbacks *allocator, VkDebugUtilsMessengerEXT *debug_messenger);

void destroy_debug_utils_messenger_ext(VkInstance instance, VkDebugUtilsMessengerEXT debug_messenger, const VkAllocationCallbacks *allocator);