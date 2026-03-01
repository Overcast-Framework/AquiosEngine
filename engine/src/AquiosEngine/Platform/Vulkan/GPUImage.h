#pragma once
#include <vulkan/vulkan.hpp>
#include <vk_mem_alloc.h>

namespace Aquios::Vulkan
{
    struct GPUImage {
        vk::Image Image;
        VmaAllocation Allocation;
    };
}