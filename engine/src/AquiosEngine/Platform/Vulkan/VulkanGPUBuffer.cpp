#include "aqpch.h"
#include "VulkanGPUBuffer.h"
#include "VKUtils.h"

#include <AquiosEngine/Renderer/CommandList.h>
#include <AquiosEngine/Renderer/Commands.h>

namespace Aquios::Vulkan
{
    VkBufferUsageFlags buftype_to_vk(GPUBuffer::Type type)
    {
        switch (type)
        {
        case GPUBuffer::Type::Vertex:
            return VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        case GPUBuffer::Type::Index:
            return VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
        case GPUBuffer::Type::StorageBlock:
            return VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
        }
    }

    void* VulkanGPUBuffer::Map(size_t offset, size_t size)
    {
        return m_AllocInfo.pMappedData; // its persistently mapped... sooo...
    }

    void VulkanGPUBuffer::UploadData(CommandList* list, void* data, size_t size, size_t offset)
    {
        auto lambdaCmd = new Commands::LambdaCmd([=]() {
            UploadData(data, size, offset);
            });

        list->Record(*lambdaCmd);
    }

    void VulkanGPUBuffer::UploadData(void* data, size_t size, size_t offset)
    {
        std::memcpy(((char*)m_AllocInfo.pMappedData) + offset, data, size);
    }

    void VulkanGPUBuffer::BindBase(CommandList* list, uint32_t bindPoint) // have to research this a bit to see if its necessary on Vk
    {
    }

    void VulkanGPUBuffer::Unmap()
    {
        vmaUnmapMemory(m_Context->GetVMAllocator(), m_Alloc);
    }

    void VulkanGPUBuffer::Free()
    {
        Unmap();
        vmaDestroyBuffer(m_Context->GetVMAllocator(), m_Buffer, m_Alloc);
    }

    void VulkanGPUBuffer::Init()
    {
        VkDeviceSize bufSize{ m_AllocatedSize };
        VkBufferCreateInfo info
        {
            .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
            .size =  bufSize,
            .usage = buftype_to_vk(m_BufferType)
        };

        if (m_BufferType == GPUBuffer::Type::StorageBlock)
            info.usage |= VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;

        VmaAllocationCreateInfo bufferAllocCI{
            .flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT | VMA_ALLOCATION_CREATE_HOST_ACCESS_ALLOW_TRANSFER_INSTEAD_BIT | VMA_ALLOCATION_CREATE_MAPPED_BIT,
            .usage = VMA_MEMORY_USAGE_AUTO
        };

        VkBuffer c_Buffer;
        vk_check(vmaCreateBuffer(m_Context->GetVMAllocator(), &info, &bufferAllocCI, &c_Buffer, &m_Alloc, &m_AllocInfo));

        m_Buffer = c_Buffer;
    }
}
