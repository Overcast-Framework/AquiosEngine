#pragma once
#include <AquiosEngine/IDestructable.h>

namespace Aquios
{
	class CommandList;

	class GPUBuffer : public IDestructable
	{
	public:
		enum class Type { Vertex, Index, UniformBlock, StorageBlock } ;
		
		GPUBuffer() = default;

		GPUBuffer(Type type, size_t size)
			: m_BufferType(type), m_AllocatedSize(size) {
		}

		Type GetType() const { return m_BufferType; }
		size_t GetAllocatedSize() const { return m_AllocatedSize; }

		virtual void* Map(size_t offset = 0, size_t size = 0) = 0;
		virtual void UploadData(CommandList* list, void* data, size_t size, size_t offset = 0) = 0;
		virtual void UploadData(void* data, size_t size, size_t offset = 0) = 0; // reprise, rejoice, I finally added this shit
		virtual void BindBase(CommandList* list, uint32_t bindPoint = 0) = 0;
		virtual void Unmap() = 0;
		virtual void Free() = 0;

		virtual void Release() override
		{
			Free();
		}

		virtual ~GPUBuffer() = default;
	protected:
		Type m_BufferType;
		size_t m_AllocatedSize;

		virtual void Init() = 0;
	};
}