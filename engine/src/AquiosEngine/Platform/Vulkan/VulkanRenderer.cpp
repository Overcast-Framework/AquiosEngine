#include "aqpch.h"
#include "VulkanRenderer.h"

#include "VulkanGPUBuffer.h"

namespace Aquios::Vulkan
{
	void VulkanRenderer::Init(GraphicsContext* ctx)
	{
		ctx->Init();
		m_Context = ctx;
	}

	void VulkanRenderer::BeginFrame()
	{
		m_Camera->UpdateMatrices();
		ResetTimer();

		m_CurrentFrameIndex = (m_CurrentFrameIndex + 1) % MaxFramesInFlight;
	}

	void VulkanRenderer::EndFrame()
	{
		EndFrameTimer();
		m_FrameCount++;
	}

	void VulkanRenderer::OnResize(int w, int h)
	{
		m_Camera->SetScreenDimensions({ w,h });
	}

	Scope<GPUBuffer> VulkanRenderer::CreateGPUBuffer(GPUBuffer::Type type, uint32_t size)
	{
		return std::make_unique<Aquios::Vulkan::VulkanGPUBuffer>(m_Context, type, size);;
	}

	Scope<CommandList> VulkanRenderer::CreateCommandList(bool immediateMode)
	{
		return Scope<CommandList>();
	}

	Scope<Pipeline> VulkanRenderer::CreatePipeline(const PipelineSpec* spec)
	{
		return Scope<Pipeline>();
	}

	Scope<Shader> VulkanRenderer::CreateShader(ShaderType type, std::string source)
	{
		return Scope<Shader>();
	}

	Scope<Texture> VulkanRenderer::CreateTexture(Texture::Type type, Format fmt, const void* data, size_t width, size_t height)
	{
		return Scope<Texture>();
	}

	Ref<VertexLayout> VulkanRenderer::GetDefaultVertexLayout()
	{
		return Ref<VertexLayout>();
	}

	void VulkanRenderer::DrawIndexed(int vertCount)
	{
	}

	void VulkanRenderer::DrawInstanced(int vertCount, int instanceCount)
	{
	}

	void VulkanRenderer::Release()
	{
	}
}