#pragma once
#include <AquiosEngine/Renderer/GPUBuffer.h>
#include "VulkanContext.h"
#include <vulkan/vulkan.hpp>
#include <vk_mem_alloc.h>

namespace Aquios::Vulkan
{
	class VulkanGPUBuffer : public GPUBuffer
	{
	public:
		void* Map(size_t offset, size_t size) override;
		void UploadData(CommandList* list, void* data, size_t size, size_t offset) override;
		void UploadData(void* data, size_t size, size_t offset) override;
		void BindBase(CommandList* list, uint32_t bindPoint) override;
		void Unmap() override;
		void Free() override;
		void Init() override;

		VulkanGPUBuffer(VulkanContext* ctx, GPUBuffer::Type type, size_t size) 
			: m_Context(ctx), GPUBuffer(type, size) {
			Init();
		}
	private:
		vk::Buffer m_Buffer;
		VmaAllocation m_Alloc;
		VmaAllocationInfo m_AllocInfo;

		VulkanContext* m_Context;
	};
}