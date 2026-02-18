#include "aqpch.h"
#include "OpenGLCommandBackend.h"

#include <AquiosEngine/Platform/OpenGL/GLGPUBuffer.h>
#include <AquiosEngine/Platform/OpenGL/OpenGLShader.h>
#include <AquiosEngine/Platform/OpenGL/OpenGLPipeline.h>
#include <AquiosEngine/Platform/OpenGL/OpenGLVertexLayout.h>
#include <AquiosEngine/Renderer/Commands.h>
#include <AquiosEngine/Renderer/Mesh.h>

#include <glad/glad.h>

using namespace Aquios::Commands;

void Aquios::OpenGL::OpenGLCommandBackend::Execute(const ClearColorCmd* cmd)
{
	glClearColor(cmd->r, cmd->g, cmd->b, cmd->a);
}

void Aquios::OpenGL::OpenGLCommandBackend::Execute(const ClearCmd* cmd)
{
	GLuint flags = cmd->clearOptions.ColorBit ? GL_COLOR_BUFFER_BIT : 0 &
		cmd->clearOptions.DepthBit ? GL_DEPTH_BUFFER_BIT : 0;

	glClear(flags);
}

void Aquios::OpenGL::OpenGLCommandBackend::Execute(const UploadBufferDataCmd* cmd)
{
	auto* glBuffer = dynamic_cast<GLGPUBuffer*>(cmd->buffer);

	std::memcpy(reinterpret_cast<uint8_t*>(glBuffer->GetMappedPtr()) + cmd->offset, 
		cmd->data.data(), 
		cmd->size);
}

void Aquios::OpenGL::OpenGLCommandBackend::Execute(const Commands::BindBufferBaseCmd* cmd)
{
	auto* glBuffer = dynamic_cast<GLGPUBuffer*>(cmd->buffer);

	if (cmd->buffer->GetType() == GPUBuffer::Type::StorageBlock)
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, cmd->bindPoint, glBuffer->GetBufferId());
}

void Aquios::OpenGL::OpenGLCommandBackend::Execute(const Commands::SetShaderUniformBufferCmd* cmd)
{

}

void Aquios::OpenGL::OpenGLCommandBackend::Execute(const Commands::SetShaderStorageBlockCmd* cmd)
{
	auto* glBuffer = dynamic_cast<GLGPUBuffer*>(cmd->buffer);

	if (cmd->buffer->GetType() == GPUBuffer::Type::StorageBlock)
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, cmd->index, glBuffer->GetBufferId());
}

void Aquios::OpenGL::OpenGLCommandBackend::Execute(const Commands::BindPipelineCmd* cmd)
{
	Aquios::OpenGL::OpenGLPipeline* pipeline = (OpenGLPipeline*)cmd->pipeline;
	switch (pipeline->GetSpec()->Type)
	{
		case PipelineType::Graphics:
		{
			GraphicsPipelineSpec* graphicsSpec = (GraphicsPipelineSpec*)pipeline->GetSpec();
			OpenGLVertexLayout* layout = (OpenGLVertexLayout*)graphicsSpec->VertexLayout;
			glBindVertexArray(layout->GetId());
		}
	}
	glUseProgram(pipeline->GetProgramId());
}

void Aquios::OpenGL::OpenGLCommandBackend::Execute(const Commands::DrawMeshCmd* cmd)
{
	auto* mesh = cmd->mesh;
	glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, 0);
}
