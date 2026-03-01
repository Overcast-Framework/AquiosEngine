#pragma once
#include "GPUImage.h"
#include <AquiosEngine/IDestructable.h>
#include <vulkan/vulkan.hpp>

namespace Aquios::Vulkan
{
	class VulkanContext;

	class Swapchain : public IDestructable
	{
	public:
		Swapchain(VulkanContext* ctx)
			: m_Context(ctx) {
			Init();
		}


		void Init();
		void Release() override;
	private:
		vk::SwapchainKHR m_Swapchain;
		VulkanContext* m_Context;

		std::vector<VkImage> m_Images;
		std::vector<VkImageView> m_ImageViews;

		GPUImage m_DepthImage;
		vk::ImageView m_DepthImageView;
	};
}