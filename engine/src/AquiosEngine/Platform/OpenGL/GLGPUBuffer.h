#pragma once
#include <AquiosEngine/Renderer/GPUBuffer.h>
#include <AquiosEngine/Platform/OpenGL/Utils.h>

namespace Aquios::OpenGL
{
	class GLGPUBuffer : public GPUBuffer
	{
	public:
		void* Map(size_t offset, size_t size) override;
		void Unmap() override;

		void Free() override;

		void UploadData(CommandList* list, void* data, size_t size, size_t offset) override;
		void UploadData(void* data, size_t size, size_t offset) override;

		void BindBase(CommandList* list, uint32_t bindPoint) override;

		GLid& GetBufferId() { return m_BufferId; }

		void* GetMappedPtr() { return m_MappedData; }

		GLGPUBuffer(GPUBuffer::Type type, size_t size)
			: GPUBuffer(type, size) {
			Init();
		}
	private:
		GLid m_BufferId = 0;
		void* m_MappedData = nullptr;

		void Init() override;
	};
}