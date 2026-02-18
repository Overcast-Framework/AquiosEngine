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
	this->m_Context = ctx;

	VertexLayout* vertLayout = new OpenGLVertexLayout();

	vertLayout->AddAttribute(VertexAttribute{ "Position",  0,  Format::Float3,  offsetof(Vertex, Position),  3, VertexAttribute::InputRate::PerVertex });
	vertLayout->AddAttribute(VertexAttribute{ "Normal",    1,  Format::Float3,  offsetof(Vertex, Normal),    3, VertexAttribute::InputRate::PerVertex });
	vertLayout->AddAttribute(VertexAttribute{ "Tangent",   2,  Format::Float3,  offsetof(Vertex, Tangent),   3, VertexAttribute::InputRate::PerVertex });
	vertLayout->AddAttribute(VertexAttribute{ "Bitangent", 3,  Format::Float3,  offsetof(Vertex, Bitangent), 3, VertexAttribute::InputRate::PerVertex });
	vertLayout->AddAttribute(VertexAttribute{ "TexCoord",  4,  Format::Float2,  offsetof(Vertex, TexCoord),  2, VertexAttribute::InputRate::PerVertex });

	vertLayout->Build();

	this->m_DefaultLayout = vertLayout;

	m_QuadTransformSSBO = this->CreateGPUBuffer(GPUBuffer::Type::StorageBlock, MAX_QUADS_PER_FRAME * sizeof(glm::mat4));
	m_QuadColorSSBO = this->CreateGPUBuffer(GPUBuffer::Type::StorageBlock, MAX_QUADS_PER_FRAME * sizeof(glm::vec4));
	m_QuadTransforms.reserve(MAX_QUADS_PER_FRAME);
	m_QuadColors.reserve(MAX_QUADS_PER_FRAME);

	m_Camera = new OrthographicCamera({ 0,0,1 }, { 0,1,0 }, { 0,0,0 }, { ActiveWindow->GetWidth(), ActiveWindow->GetHeight() });
}

void Aquios::OpenGL::OpenGLRenderer::BeginFrame()
{
	m_Camera->Update();

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
	m_QuadTransformSSBO->Release();
}

Aquios::GPUBuffer* Aquios::OpenGL::OpenGLRenderer::CreateGPUBuffer(GPUBuffer::Type type, uint32_t size)
{
	auto* buffer = new Aquios::OpenGL::GLGPUBuffer(type, size);
	return buffer;
}

Aquios::CommandList* Aquios::OpenGL::OpenGLRenderer::CreateCommandList(bool immediateMode)
{
	Aquios::CommandList* commandList = new Aquios::CommandList();
	commandList->ExecuteImmediate = immediateMode;
	commandList->SetBackend(new Aquios::OpenGL::OpenGLCommandBackend());

	return commandList;
}

Aquios::VertexLayout* Aquios::OpenGL::OpenGLRenderer::GetDefaultVertexLayout()
{
	return this->m_DefaultLayout;
}

Aquios::Pipeline* Aquios::OpenGL::OpenGLRenderer::CreatePipeline(const PipelineSpec* spec)
{
	Aquios::Pipeline* pipeline = new OpenGL::OpenGLPipeline(spec);
	return pipeline;
}

Aquios::Shader* Aquios::OpenGL::OpenGLRenderer::CreateShader(ShaderType type, std::string source)
{
	Aquios::Shader* shader = new OpenGL::OpenGLShader(type, source);
	return shader;
}

void Aquios::OpenGL::OpenGLRenderer::DrawQuad(glm::vec4 color, glm::vec3 position, glm::vec3 scale, float rotation)
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1.0f))
		* glm::scale(glm::mat4(1.0f), scale);
	m_QuadTransforms.push_back(m_Camera->GetProjectionMatrix() * m_Camera->GetViewMatrix() * transform);
	m_QuadColors.push_back(color);
}

void Aquios::OpenGL::OpenGLRenderer::FlushQuadBatch()
{
	if (m_QuadTransforms.empty())
		return;

	if (m_QuadMesh == nullptr)
	{
		std::vector<Aquios::Vertex> quad_vertices
		{
			VERTEXFPOS_TEX(-0.5f,- 0.5f, 0,   0,0),
			VERTEXFPOS_TEX(-0.5f,  0.5f, 0,   0,1),
			VERTEXFPOS_TEX( 0.5f, -0.5f, 0,   1,0),
			VERTEXFPOS_TEX( 0.5f,  0.5f, 0,   1,1)
		};

		std::vector<uint32_t> quad_indices
		{
			0,1,2,
			2,1,3
		};

		m_QuadMesh = new Aquios::Mesh(quad_vertices, quad_indices, this->m_DefaultMats.Basic);
	}

	m_QuadMesh->SetMaterial(this->m_DefaultMats.Basic);

	auto* instCmdList = this->CreateCommandList(true);
	m_QuadMesh->GetMaterial()->Use(instCmdList);
	m_QuadTransformSSBO->BindBase(instCmdList, 1);
	m_QuadColorSSBO->BindBase(instCmdList, 2);
	instCmdList->Release();

	m_QuadTransformSSBO->UploadData(m_QuadTransforms.data(), m_QuadTransforms.size() * sizeof(glm::mat4));
	m_QuadColorSSBO->UploadData(m_QuadColors.data(), m_QuadColors.size() * sizeof(glm::vec4));

	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, m_QuadTransforms.size());

	Stats.QuadCount = m_QuadTransforms.size();
	Stats.DrawCalls++;
	m_QuadTransforms.clear();
	m_QuadColors.clear();
}

void Aquios::OpenGL::OpenGLRenderer::OnResize(int w, int h)
{
	m_Camera->ScreenDimensions = { w,h };
}

void Aquios::OpenGL::OpenGLRenderer::DrawIndexed(CommandList* cmdList, VertexLayout* layout, Pipeline* pipeline, GPUBuffer* vertexBuffer, GPUBuffer* indexBuffer)
{
}

void Aquios::OpenGL::OpenGLRenderer::DrawMesh(CommandList* cmdList, Mesh* mesh)
{
	mesh->GetMaterial()->Use(cmdList);
	cmdList->Record(Commands::DrawMeshCmd(mesh));
	Stats.MeshCount++;
	Stats.DrawCalls++;
}
