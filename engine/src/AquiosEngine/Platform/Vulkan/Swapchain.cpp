#include "aqpch.h"
#include "Swapchain.h"
#include "VKUtils.h"

#include <AquiosEngine/Platform/Vulkan/VulkanContext.h>
#include <glfw/glfw3.h>

namespace Aquios::Vulkan
{
	void Swapchain::Init()
	{
        const VkFormat imageFormat{ VK_FORMAT_B8G8R8A8_SRGB };
        auto& dev = m_Context->GetDevice();

        VkSwapchainCreateInfoKHR swapchainCI{
            .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
            .surface = m_Context->GetSurface(),
            .minImageCount = m_Context->GetSurfaceCaps().minImageCount,
            .imageFormat = imageFormat,
            .imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR,
            .imageExtent{ .width = m_Context->GetSurfaceCaps().currentExtent.width, .height = m_Context->GetSurfaceCaps().currentExtent.height },
            .imageArrayLayers = 1,
            .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
            .preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
            .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
            .presentMode = VK_PRESENT_MODE_FIFO_KHR
        };

        VkSwapchainKHR c_Swapchain;
        vk_check(vkCreateSwapchainKHR(dev, &swapchainCI, nullptr, &c_Swapchain));

        m_Swapchain = c_Swapchain;

        uint32_t imageCount{ 0 };
        vk_check(vkGetSwapchainImagesKHR(dev, m_Swapchain, &imageCount, nullptr));
        m_Images.resize(imageCount);
        vk_check(vkGetSwapchainImagesKHR(dev, m_Swapchain, &imageCount, m_Images.data()));
        m_ImageViews.resize(imageCount);

        std::vector<VkFormat> depthFormatList{ VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT };
        VkFormat depthFormat{ VK_FORMAT_UNDEFINED };
        for (VkFormat& format : depthFormatList) {
            VkFormatProperties2 formatProperties{ .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2 };
            vkGetPhysicalDeviceFormatProperties2(m_Context->GetPhysicalDevice(), format, &formatProperties);
            if (formatProperties.formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
                depthFormat = format;
                break;
            }
        }

        VkImageCreateInfo depthImageCI{
            .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .imageType = VK_IMAGE_TYPE_2D,
            .format = depthFormat,
            .extent{.width = m_Context->GetSurfaceCaps().currentExtent.width, .height = m_Context->GetSurfaceCaps().currentExtent.height, .depth = 1 },
            .mipLevels = 1,
            .arrayLayers = 1,
            .samples = VK_SAMPLE_COUNT_1_BIT,
            .tiling = VK_IMAGE_TILING_OPTIMAL,
            .usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
            .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        };

        VmaAllocationCreateInfo allocCI{
            .flags = VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT,
            .usage = VMA_MEMORY_USAGE_AUTO
        };

        VkImage c_DepthImage;
        vk_check(vmaCreateImage(m_Context->GetVMAllocator(), &depthImageCI, &allocCI, &c_DepthImage, &m_DepthImage.Allocation, nullptr));

        m_DepthImage.Image = c_DepthImage;

        VkImageViewCreateInfo depthViewCI{
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .image = m_DepthImage.Image,
            .viewType = VK_IMAGE_VIEW_TYPE_2D,
            .format = depthFormat,
            .subresourceRange{.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT, .levelCount = 1, .layerCount = 1 }
        };

        VkImageView c_DepthImageView;
        vk_check(vkCreateImageView(dev, &depthViewCI, nullptr, &c_DepthImageView));

        m_DepthImageView = c_DepthImageView;
	}

	void Swapchain::Release()
	{
        vmaDestroyImage(m_Context->GetVMAllocator(), m_DepthImage.Image, m_DepthImage.Allocation);
	}
}
