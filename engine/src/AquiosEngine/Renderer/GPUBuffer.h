#pragma once
#include <AquiosEngine/Renderer/CommandList.h>
#include <AquiosEngine/IDestructable.h>

namespace Aquios
{
	class GPUBuffer : public IDestructable
	{
	public:
		enum class Type { Vertex, Index, UniformBlock, StorageBlock } ;
		
		explicit GPUBuffer(Type type, size_t size)
			: m_BufferType(type), m_AllocatedSize(size) {
		}

		Type GetType() const { return m_BufferType; }
		size_t GetAllocatedSize() const { return m_AllocatedSize; }

		virtual void* Map(CommandList* list, size_t offset = 0, size_t size = 0) = 0;
		virtual void Unmap(CommandList* list) = 0;
		virtual void Free() = 0;

		virtual void Release() override
		{
			Free();
		}

		virtual ~GPUBuffer() = default;
	private:
		Type m_BufferType;
		size_t m_AllocatedSize;
	};
}