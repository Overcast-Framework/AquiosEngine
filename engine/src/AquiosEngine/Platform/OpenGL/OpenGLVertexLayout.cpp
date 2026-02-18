#include "aqpch.h"
#include "OpenGLVertexLayout.h"

#include <AquiosEngine/Renderer/Format.h>
#include <AquiosEngine/Platform/OpenGL/GLGPUBuffer.h>
#include <glad/glad.h>

void Aquios::OpenGL::OpenGLVertexLayout::AddAttribute(const VertexAttribute& attrib)
{
	this->m_Attributes.emplace_back(attrib);
}

void Aquios::OpenGL::OpenGLVertexLayout::Build()
{
	glCreateVertexArrays(1, &this->m_VAOId);

	int i = 0;
	for (auto& attrib : m_Attributes)
	{
		glEnableVertexArrayAttrib(this->m_VAOId, attrib.SemanticIndex);
		glVertexArrayAttribFormat(this->m_VAOId, attrib.SemanticIndex, attrib.Stride, format_to_gl(attrib.AttribFormat), false, attrib.Offset);
		glVertexArrayAttribBinding(this->m_VAOId, attrib.SemanticIndex, 0);
		i++;
	}
}

void Aquios::OpenGL::OpenGLVertexLayout::Release()
{
	glDeleteVertexArrays(1, &this->m_VAOId);
}

void Aquios::OpenGL::OpenGLVertexLayout::AssignBuffer(GPUBuffer* buf, uint32_t bindingIndex, size_t stride)
{
	auto* buffer = dynamic_cast<GLGPUBuffer*>(buf);
	AQ_CORE_ASSERT(buf->GetType() == GPUBuffer::Type::Vertex || buf->GetType() == GPUBuffer::Type::Index, "You can only assign vertex and index buffers to vertex layouts.");
	
	if (buf->GetType() == GPUBuffer::Type::Vertex)
	{
		glVertexArrayVertexBuffer(this->m_VAOId, bindingIndex, buffer->GetBufferId(), 0, stride);
	}
	else
		glVertexArrayElementBuffer(this->m_VAOId, buffer->GetBufferId());
}
