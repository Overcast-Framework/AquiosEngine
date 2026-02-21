#include "aqpch.h"
#include "Mesh.h"

#include <AquiosEngine/Application.h>

Aquios::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, Material* material)
{
	this->m_Material = material;

	auto renderer = Aquios::Application::Get().GetActiveWindow().GetRenderer();
	this->m_VertexBuffer = renderer->CreateGPUBuffer(GPUBuffer::Type::Vertex, vertices.size() * sizeof(Vertex));
	this->m_IndexBuffer = renderer->CreateGPUBuffer(GPUBuffer::Type::Index, indices.size() * sizeof(uint32_t));

	this->m_VertexBuffer->UploadData(vertices.data(), vertices.size() * sizeof(Vertex));
	this->m_IndexBuffer->UploadData(indices.data(), indices.size() * sizeof(uint32_t));

	auto* gSpec = (GraphicsPipelineSpec*)material->GetPipeline()->GetSpec();
	gSpec->VertexLayout->AssignBuffer(this->m_VertexBuffer.get(), 0, sizeof(Aquios::Vertex));
	gSpec->VertexLayout->AssignBuffer(this->m_IndexBuffer.get());

	this->m_VertexCount = vertices.size();
	this->m_IndexCount = indices.size();
}

void Aquios::Mesh::UpdateData(CommandList* list, std::vector<Vertex> vertices, std::vector<uint32_t> indices)
{
	auto renderer = Aquios::Application::Get().GetActiveWindow().GetRenderer();

	list->Record(Commands::LambdaCmd(
		[this, vertices, indices, renderer]() {
			if (m_VertexCount != vertices.size())
			{
				this->m_VertexBuffer = renderer->CreateGPUBuffer(GPUBuffer::Type::Vertex, vertices.size());
			}
			if (m_IndexCount != indices.size())
			{
				this->m_IndexBuffer = renderer->CreateGPUBuffer(GPUBuffer::Type::Index, indices.size());
			}
	}));

	this->m_VertexBuffer->UploadData(list, vertices.data(), vertices.size() * sizeof(Vertex));
	this->m_IndexBuffer->UploadData(list, indices.data(), indices.size() * sizeof(uint32_t));

	list->Record(Commands::LambdaCmd(
		[this, vertices, indices]() {
			this->m_VertexCount = vertices.size();
			this->m_IndexCount = indices.size(); 
		}
	));
}

void Aquios::Mesh::SetMaterial(Material* material)
{
	this->m_Material = material;
}

void Aquios::Mesh::Release()
{
	this->m_IndexBuffer->Free();
	this->m_VertexBuffer->Free();
}
