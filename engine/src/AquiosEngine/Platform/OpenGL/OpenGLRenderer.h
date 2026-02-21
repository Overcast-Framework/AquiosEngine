#pragma once
#include <AquiosEngine/Renderer/Renderer.h>
#include <AquiosEngine/Platform/OpenGL/OpenGLContext.h>

namespace Aquios::OpenGL
{
	class OpenGLRenderer : public Renderer
	{
	public:
		void Init(GraphicsContext* ctx) override;

		void BeginFrame() override;

		void EndFrame() override;

		void Release() override;

		void OnResize(int w, int h) override;
				
		void DrawIndexed(int vertCount) override;
		void DrawInstanced(int vertCount, int instanceCount) override;

		Scope<GPUBuffer> CreateGPUBuffer(GPUBuffer::Type type, uint32_t size) override;
		Scope<CommandList> CreateCommandList(bool immediateMode) override;
		Ref<VertexLayout> GetDefaultVertexLayout() override;
		Scope<Pipeline> CreatePipeline(const PipelineSpec* spec) override;
		Scope<Shader> CreateShader(ShaderType type, std::string source) override;
	private:
		Ref<VertexLayout> m_DefaultLayout = nullptr;
	};
}