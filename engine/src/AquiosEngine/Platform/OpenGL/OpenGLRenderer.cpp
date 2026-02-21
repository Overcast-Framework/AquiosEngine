#include "aqpch.h"
#include "OpenGLRenderer.h"

#include <AquiosEngine/Platform/OpenGL/GLGPUBuffer.h>
#include <AquiosEngine/Renderer/CommandList.h>
#include <AquiosEngine/Platform/OpenGL/OpenGLCommandBackend.h>
#include <AquiosEngine/Platform/OpenGL/OpenGLVertexLayout.h>
#include <AquiosEngine/Platform/OpenGL/OpenGLPipeline.h>
#include <AquiosEngine/Platform/OpenGL/OpenGLShader.h>
#include <AquiosEngine/Renderer/Vertex.h>
#include <AquiosEngine/Window.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Aquios::OpenGL::OpenGLRenderer::Init(GraphicsContext* ctx)
{
	ctx->Init();          
	m_Context = ctx;

	m_DefaultLayout = std::make_shared<OpenGLVertexLayout>();

	m_DefaultLayout->AddAttribute(VertexAttribute{ "Position",  0,  Format::Float3,  offsetof(Vertex, Position),  3, VertexAttribute::InputRate::PerVertex });
	m_DefaultLayout->AddAttribute(VertexAttribute{ "Normal",    1,  Format::Float3,  offsetof(Vertex, Normal),    3, VertexAttribute::InputRate::PerVertex });
	m_DefaultLayout->AddAttribute(VertexAttribute{ "Tangent",   2,  Format::Float3,  offsetof(Vertex, Tangent),   3, VertexAttribute::InputRate::PerVertex });
	m_DefaultLayout->AddAttribute(VertexAttribute{ "Bitangent", 3,  Format::Float3,  offsetof(Vertex, Bitangent), 3, VertexAttribute::InputRate::PerVertex });
	m_DefaultLayout->AddAttribute(VertexAttribute{ "TexCoord",  4,  Format::Float2,  offsetof(Vertex, TexCoord),  2, VertexAttribute::InputRate::PerVertex });

	m_DefaultLayout->Build();

	m_Renderer2D = std::make_shared<Renderer2D>();
	m_Renderer2D->Init(this);
}

void Aquios::OpenGL::OpenGLRenderer::BeginFrame()
{
	m_Camera->UpdateMatrices();

	ResetTimer();
	glClearColor(0.15f, 0.15f, 0.15f, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Aquios::OpenGL::OpenGLRenderer::EndFrame()
{
	this->m_Context->SwapBuffers();
	EndFrameTimer();
	m_FrameCount++;
}

void Aquios::OpenGL::OpenGLRenderer::Release()
{
	m_DefaultLayout->Release();
}

Scope<Aquios::GPUBuffer> Aquios::OpenGL::OpenGLRenderer::CreateGPUBuffer(GPUBuffer::Type type, uint32_t size)
{
	return std::make_unique<Aquios::OpenGL::GLGPUBuffer>(type, size);
}

Scope<Aquios::CommandList> Aquios::OpenGL::OpenGLRenderer::CreateCommandList(bool immediateMode)
{
	Scope<Aquios::CommandList> commandList = std::make_unique<Aquios::CommandList>();
	commandList->ExecuteImmediate = immediateMode;
	commandList->SetBackend(std::make_unique<Aquios::OpenGL::OpenGLCommandBackend>());

	return commandList;
}

Ref<Aquios::VertexLayout> Aquios::OpenGL::OpenGLRenderer::GetDefaultVertexLayout()
{
	return m_DefaultLayout;
}

Scope<Aquios::Pipeline> Aquios::OpenGL::OpenGLRenderer::CreatePipeline(const PipelineSpec* spec)
{
	return std::make_unique<OpenGL::OpenGLPipeline>(spec);
}

Scope<Aquios::Shader> Aquios::OpenGL::OpenGLRenderer::CreateShader(ShaderType type, std::string source)
{
	return std::make_unique<OpenGL::OpenGLShader>(type, source);
}

void Aquios::OpenGL::OpenGLRenderer::OnResize(int w, int h)
{
	m_Camera->SetScreenDimensions({ w,h });
}

void Aquios::OpenGL::OpenGLRenderer::DrawIndexed(int vertCount)
{
	glDrawElements(GL_TRIANGLES, vertCount, GL_UNSIGNED_INT, nullptr);
}

void Aquios::OpenGL::OpenGLRenderer::DrawInstanced(int vertCount, int instanceCount)
{
	glDrawElementsInstanced(GL_TRIANGLES, vertCount, GL_UNSIGNED_INT, nullptr, instanceCount);
}

/*void Aquios::OpenGL::OpenGLRenderer::DrawMesh(CommandList* cmdList, Mesh* mesh)
{
	mesh->GetMaterial()->Use(cmdList);
	cmdList->Record(Commands::DrawMeshCmd(mesh));
	Stats.MeshCount++;
	Stats.DrawCalls++;
}*/
