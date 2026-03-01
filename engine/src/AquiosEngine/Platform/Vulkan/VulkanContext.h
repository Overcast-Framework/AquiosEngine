#pragma once
#include "AquiosEngine/Renderer/GraphicsContext.h"
#include <vulkan/vulkan.hpp>
#include <VkBootstrap.h>
#include <vk_mem_alloc.h>

struct GLFWwindow;

namespace Aquios::Vulkan
{
    class VulkanContext : public GraphicsContext
    {
		public:
			VulkanContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {};

			GLFWwindow* GetWindowHandle() const { return m_WindowHandle; }

			const vkb::Instance& GetVkInstance() const { return m_Instance; }
			const vkb::PhysicalDevice& GetPhysicalDevice() const { return m_PhysicalDevice; }
			const vkb::Device& GetDevice() const { return m_Device; }

			const vk::SurfaceKHR& GetSurface() const { return m_Surface; }
			const vk::SurfaceCapabilitiesKHR& GetSurfaceCaps() const { return m_SurfaceCaps; }

			const vk::Queue& GetGraphicsQueue() const { return m_GraphicsQueue; }

			const VmaAllocator& GetVMAllocator() const { return m_VMAllocator; }

			void Init() override;
			void SwapBuffers() override;
		private:
			GLFWwindow* m_WindowHandle;
			vk::SurfaceKHR m_Surface;
			vk::SurfaceCapabilitiesKHR m_SurfaceCaps{};

			vkb::Instance m_Instance;
			vkb::PhysicalDevice m_PhysicalDevice;
			vkb::Device m_Device;

			vk::Queue m_GraphicsQueue;
			VmaAllocator m_VMAllocator;
    };
}

