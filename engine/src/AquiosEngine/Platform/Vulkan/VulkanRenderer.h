#pragma once
#include <AquiosEngine/Renderer/Renderer.h>

namespace Aquios::Vulkan
{
	class VulkanRenderer : public Renderer
	{
	public:
		void Init(GraphicsContext* ctx) override;
		void BeginFrame() override;
		void EndFrame() override;

		void OnResize(int w, int h) override;

		Scope<GPUBuffer> CreateGPUBuffer(GPUBuffer::Type type, uint32_t size) override;
		Scope<CommandList> CreateCommandList(bool immediateMode) override;
		Scope<Pipeline> CreatePipeline(const PipelineSpec* spec) override;
		Scope<Shader> CreateShader(ShaderType type, std::string source) override;
		Scope<Texture> CreateTexture(Texture::Type type, Format fmt, const void* data, size_t width, size_t height) override;
		Ref<VertexLayout> GetDefaultVertexLayout() override;

		void DrawIndexed(int vertCount) override;
		void DrawInstanced(int vertCount, int instanceCount) override;
		void Release() override;

	private:
		std::array<ShaderDataBuffer, MaxFramesInFlight> shaderDataBuffers;
		std::array<vk::CommandBuffer, MaxFramesInFlight> commandBuffers;
	};
}