#pragma once
#include <AquiosEngine/IDestructable.h>
#include <AquiosEngine/Renderer/Pipeline.h>
#include <AquiosEngine/Renderer/Texture.h>

#include <glm/glm.hpp>

namespace Aquios
{
	struct MaterialUB
	{
		glm::vec4 m_BaseColor = glm::vec4(0, 0, 0, 0);
		float m_Roughness = 0.5f;
	};

	class Material : public IDestructable
	{
	public:
		explicit Material(Pipeline* pipeline) : m_Pipeline(pipeline) { Initialize(); };

		void SetTextureInSlot(uint32_t slot, Texture* texture);
		void SetBaseColor(glm::vec4 color);
		void SetRoughness(float roughness);

		void Use(CommandList* list);
		void Update();

		void SetUBStruct(MaterialUB* ubStruct, size_t structSize);
		MaterialUB* GetUBStruct();
		void MarkDirty();

		Pipeline* GetPipeline() { return m_Pipeline; }

		void Release() override;
	private:
		Pipeline* m_Pipeline = nullptr;
		Texture* m_Textures[16] = { nullptr };

		MaterialUB* m_UBStruct = {};
		Scope<GPUBuffer> m_MaterialUB = nullptr;

		size_t m_UBStructSize = 0;

		bool m_IsUBStructDirty = false;

		void Initialize();
	};
}