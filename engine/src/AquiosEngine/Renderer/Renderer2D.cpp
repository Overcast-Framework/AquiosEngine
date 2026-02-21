#include "aqpch.h"
#include "Renderer2D.h"

#include <AquiosEngine/Application.h>
#include <AquiosEngine/Renderer/Renderer.h>

#include <glm/gtc/matrix_transform.hpp>

void Aquios::Renderer2D::Init(Renderer* renderer)
{
	m_Renderer = renderer;

	std::vector<Aquios::Vertex> quad_vertices
	{
		VERTEXFPOS_TEX(-0.5f, -0.5f, 0, 0, 0),
		VERTEXFPOS_TEX(-0.5f,  0.5f, 0, 0, 1),
		VERTEXFPOS_TEX( 0.5f, -0.5f, 0, 1, 0),
		VERTEXFPOS_TEX( 0.5f,  0.5f, 0, 1, 1)
	};

	std::vector<uint32_t> quad_indices
	{
		0,1,2,
		2,1,3
	};

	size_t vtxSize = quad_vertices.size() * sizeof(Vertex);
	size_t idxSize = quad_indices.size() * sizeof(uint32_t);

	m_QuadVertexBuffer = m_Renderer->CreateGPUBuffer(GPUBuffer::Type::Vertex, vtxSize);
	m_QuadIndexBuffer = m_Renderer->CreateGPUBuffer(GPUBuffer::Type::Index, idxSize);
	m_QuadVertexBuffer->UploadData(quad_vertices.data(), vtxSize);
	m_QuadIndexBuffer->UploadData(quad_indices.data(), idxSize);

	m_SubmittedQuads.reserve(MAX_QUADS_PER_FRAME);
	m_QuadSSBO = m_Renderer->CreateGPUBuffer(GPUBuffer::Type::StorageBlock, MAX_QUADS_PER_FRAME * sizeof(Int_QuadInfo));

	std::ifstream basic_vifs("engine/assets/shaders/glsl/basic_vs.glsl"); // to-do: reconsider something here potentially, maybe when I got the ShaderLibrary working
	std::string basic_vsContent((std::istreambuf_iterator<char>(basic_vifs)),
		(std::istreambuf_iterator<char>()));
	std::ifstream basic_fifs("engine/assets/shaders/glsl/basic_fs.glsl");
	std::string basic_fsContent((std::istreambuf_iterator<char>(basic_fifs)),
		(std::istreambuf_iterator<char>()));

	if (!basic_vifs)
		AQ_CORE_ERROR("Couldn't read from basic_vs.glsl");
	if (!basic_fifs)
		AQ_CORE_ERROR("Couldn't read from basic_fs.glsl");

	auto vsShader = m_Renderer->CreateShader(Aquios::ShaderType::Vertex, basic_vsContent);
	auto fsShader = m_Renderer->CreateShader(Aquios::ShaderType::Fragment, basic_fsContent);

	auto* pipelineSpec = new Aquios::GraphicsPipelineSpec();
	pipelineSpec->VertexShader = std::move(vsShader);
	pipelineSpec->FragmentShader = std::move(fsShader); // I can change this back once ShaderLibrary is up
	pipelineSpec->VertexLayout = m_Renderer->GetDefaultVertexLayout();

	pipelineSpec->VertexLayout->AssignBuffer(m_QuadVertexBuffer.get(), 0, sizeof(Aquios::Vertex));
	pipelineSpec->VertexLayout->AssignBuffer(m_QuadIndexBuffer.get());

	m_QuadShaders = m_Renderer->CreatePipeline(pipelineSpec);

	m_InstantCmdList = m_Renderer->CreateCommandList(true);
}

void Aquios::Renderer2D::DrawQuad(glm::vec4 color, glm::vec3 position, glm::vec3 scale, float rotation)
{
	Int_QuadInfo info;
	info.Color = color;
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1.0f))
		* glm::scale(glm::mat4(1.0f), scale);

	auto* camera = m_Renderer->GetCamera();
	info.MVP = camera->GetProjectionMatrix() * camera->GetViewMatrix() * transform;

	m_SubmittedQuads.push_back(info);
}

void Aquios::Renderer2D::SubmitBatch()
{
	m_QuadSSBO->UploadData(m_SubmittedQuads.data(), MAX_QUADS_PER_FRAME * sizeof(Int_QuadInfo));

	m_QuadShaders->Bind(m_InstantCmdList.get());
	m_QuadSSBO->BindBase(m_InstantCmdList.get(), 0);

	m_Renderer->DrawInstanced(6, m_SubmittedQuads.size());

	m_Renderer->Stats.QuadCount = m_SubmittedQuads.size();
	m_Renderer->Stats.DrawCalls++;

	m_SubmittedQuads.clear();
}

void Aquios::Renderer2D::Release()
{
	m_InstantCmdList->Release();
}
