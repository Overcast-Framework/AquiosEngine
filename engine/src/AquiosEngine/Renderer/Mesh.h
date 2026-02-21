#pragma once
#include <AquiosEngine/IDestructable.h>
#include <AquiosEngine/Renderer/GPUBuffer.h>
#include <AquiosEngine/Renderer/VertexLayout.h>
#include <AquiosEngine/Renderer/Vertex.h>
#include <AquiosEngine/Renderer/Material.h>
#include <AquiosEngine/Renderer/CommandList.h>

namespace Aquios
{
	class Mesh : public IDestructable
	{
	public:
		explicit Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, Material* material);

		void UpdateData(CommandList* list, std::vector<Vertex> vertices, std::vector<uint32_t> indices);
		void SetMaterial(Material* material);

		GPUBuffer* GetVertexBuffer() { return m_VertexBuffer.get(); }
		GPUBuffer* GetIndexBuffer() { return m_IndexBuffer.get(); }
		Material* GetMaterial() { return m_Material; }

		const uint32_t& GetIndexCount() { return m_IndexCount; }
		const uint32_t& GetVertexCount() { return m_VertexCount; }

		void Release() override;
	private:
		Scope<GPUBuffer> m_VertexBuffer = nullptr;
		Scope<GPUBuffer> m_IndexBuffer = nullptr;
		VertexLayout* m_Layout = nullptr;
		Material* m_Material = nullptr;

		uint32_t m_VertexCount = 0;
		uint32_t m_IndexCount = 0;
	};
}