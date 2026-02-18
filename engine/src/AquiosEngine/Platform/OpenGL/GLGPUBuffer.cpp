#include "aqpch.h"
#include "GLGPUBuffer.h"

#include <AquiosEngine/Renderer/CommandList.h>
#include <AquiosEngine/Renderer/Commands.h>

#include <glad/glad.h>

void* Aquios::OpenGL::GLGPUBuffer::Map(size_t offset, size_t size)
{
	this->m_MappedData = glMapNamedBufferRange(this->m_BufferId, offset, size, GL_MAP_PERSISTENT_BIT | GL_MAP_WRITE_BIT | GL_MAP_COHERENT_BIT);
	if (this->m_MappedData == nullptr)
	{
		AQ_CORE_FATAL("[OPENGL]: Mapped buffer data is nullptr (buffer id: {0})", this->m_BufferId);
	}

	return this->m_MappedData;
}

void Aquios::OpenGL::GLGPUBuffer::Unmap()
{
	glUnmapNamedBuffer(this->m_BufferId);
}

void Aquios::OpenGL::GLGPUBuffer::Free()
{
	this->Unmap();
	glDeleteBuffers(1, &this->m_BufferId);
}

void Aquios::OpenGL::GLGPUBuffer::UploadData(CommandList* list, void* data, size_t size, size_t offset)
{
	auto command = Commands::UploadBufferDataCmd(this, data, size, offset);
	list->Record(command);
}

void Aquios::OpenGL::GLGPUBuffer::UploadData(void* data, size_t size, size_t offset)
{
	std::memcpy(reinterpret_cast<uint8_t*>(this->GetMappedPtr()) + offset,
		data,
		size);
}

void Aquios::OpenGL::GLGPUBuffer::Init()
{
	glCreateBuffers(1, &this->m_BufferId);
	glNamedBufferStorage(this->m_BufferId, this->m_AllocatedSize, nullptr, GL_DYNAMIC_STORAGE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT | GL_MAP_WRITE_BIT);
	Map(0, this->GetAllocatedSize());
}

void Aquios::OpenGL::GLGPUBuffer::BindBase(CommandList* list, uint32_t bindPoint)
{
	list->Record(Commands::BindBufferBaseCmd(bindPoint, this));
}
