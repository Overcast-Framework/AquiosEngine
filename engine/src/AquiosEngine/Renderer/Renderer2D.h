#pragma once
#include <glm/glm.hpp>
#include <AquiosEngine/Renderer/GPUBuffer.h>
#include <AquiosEngine/Renderer/VertexLayout.h>
#include <AquiosEngine/Renderer/Texture.h>
#include <AquiosEngine/Renderer/Pipeline.h>

namespace Aquios
{
	class Renderer;

	struct Int_QuadInfo
	{
		glm::vec4 Color;
		glm::mat4 MVP;
		uint64_t TextureHandle;
	};

	class Renderer2D : public IDestructable
	{
	public:
		const int MAX_QUADS_PER_FRAME = 20000;

		void Init(Renderer* renderer);

		void DrawQuad(glm::vec4 color, glm::vec3 position, glm::vec3 scale, float rotation = 0, Texture* tex = nullptr);
		void SubmitBatch();

		void Release() override;
	private:
		std::vector<Int_QuadInfo> m_SubmittedQuads;
		GPUBuffer* m_QuadSSBO;

		PerFrameBuffers m_QuadSSBOs;

		Scope<GPUBuffer> m_QuadVertexBuffer;
		Scope<GPUBuffer> m_QuadIndexBuffer;
		Scope<Pipeline> m_QuadShaders;
		Scope<Texture> m_QuadDefaultTex;

		Scope<CommandList> m_InstantCmdList;

		Renderer* m_Renderer;
	};
}