#pragma once
#include <AquiosEngine/Renderer/Renderer.h>
#include <AquiosEngine/Platform/OpenGL/OpenGLContext.h>

namespace Aquios::OpenGL
{
	class OpenGLRenderer : public Renderer
	{
	public:
		const int MAX_QUADS_PER_FRAME = 20000;

		void Init(GraphicsContext* ctx) override;

		void BeginFrame() override;

		void DrawIndexed(CommandList* cmdList, VertexLayout* layout, Pipeline* pipeline, GPUBuffer* vertexBuffer, GPUBuffer* indexBuffer) override;
		void DrawMesh(CommandList* cmdList, Mesh*) override;

		void EndFrame() override;

		void Release() override;

		GPUBuffer* CreateGPUBuffer(GPUBuffer::Type type, uint32_t size) override;
		CommandList* CreateCommandList(bool immediateMode) override;
		VertexLayout* GetDefaultVertexLayout() override;
		Pipeline* CreatePipeline(const PipelineSpec* spec) override;
		Shader* CreateShader(ShaderType type, std::string source) override;
		void DrawQuad(glm::vec4 color, glm::vec3 position, glm::vec3 scale, float rotation) override;

		void FlushQuadBatch() override;
	private:
		VertexLayout* m_DefaultLayout = nullptr;
		GPUBuffer* m_QuadTransformSSBO = nullptr;
		GPUBuffer* m_QuadColorSSBO = nullptr;

		std::vector<glm::mat4> m_QuadTransforms;
		std::vector<glm::vec4> m_QuadColors;

		Mesh* m_QuadMesh = nullptr;
		bool m_QTUploaded = false;

		void OnResize(int w, int h) override;
	};
}