#pragma once
#include <vulkan/vulkan.h>

#define vk_check(result) if(result != VkResult::VK_SUCCESS) { AQ_CORE_ERROR("[VK] Vulkan Function Failed! At {}:{} Result code {}.", __FILE__, __LINE__, (int)result); }
#define vk_check_info(result, extraInfo) if(result != VkResult::VK_SUCCESS) { AQ_CORE_ERROR("[VK] Vulkan Function Failed! Result code {}. Extra Info: {}", (int)result, extraInfo); }