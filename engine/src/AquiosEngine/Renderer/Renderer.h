#pragma once
#include <AquiosEngine/IDestructable.h>
#include <AquiosEngine/Renderer/GraphicsContext.h>
#include <AquiosEngine/Renderer/GPUBuffer.h>
#include <AquiosEngine/Renderer/VertexLayout.h>
#include <AquiosEngine/Renderer/Pipeline.h>
#include <AquiosEngine/Renderer/Mesh.h>
#include <AquiosEngine/Renderer/OrthographicCamera.h>
#include <fstream>
#include <chrono>

namespace Aquios
{
	class Window;

	class Renderer : public IDestructable
	{
	public:
		struct DefaultMaterials
		{
			Material* Basic;
			bool Initialized;
		};

		struct Statistics
		{
			int QuadCount;
			int MeshCount;
			int DrawCalls;
		} Stats;

		Window* ActiveWindow = nullptr;

		virtual void Init(GraphicsContext* ctx) = 0;

		virtual void BeginFrame() = 0;
		virtual void EndFrame() = 0;

		virtual void OnResize(int w, int h) = 0;

		virtual GPUBuffer* CreateGPUBuffer(GPUBuffer::Type type, uint32_t size) = 0;
		virtual CommandList* CreateCommandList(bool immediateMode = false) = 0;
		virtual Pipeline* CreatePipeline(const PipelineSpec* spec) = 0;
		virtual Shader* CreateShader(ShaderType type, std::string source) = 0;
		virtual VertexLayout* GetDefaultVertexLayout() = 0;
		
		virtual void DrawIndexed(CommandList* cmdList, VertexLayout* layout, Pipeline* pipeline, GPUBuffer* vertexBuffer, GPUBuffer* indexBuffer) = 0;
		virtual void DrawMesh(CommandList* cmdList, Mesh* mesh) = 0;
		virtual void DrawQuad(glm::vec4 color, glm::vec3 position, glm::vec3 scale, float rotation) = 0;

		virtual void FlushQuadBatch() = 0;

		void CreateDefaultMats();

		const DefaultMaterials& GetDefaultMaterials() const { return m_DefaultMats; }
		const float& GetDeltaTime() const { return m_DeltaTime; }
		const int& GetFPS() const { return m_FPS; }
		const int& GetFrameCount() const { return m_FrameCount; }

		virtual void Release() = 0;
		virtual ~Renderer() = default;
	protected:
		GraphicsContext* m_Context = nullptr;
		DefaultMaterials m_DefaultMats;
		OrthographicCamera* m_Camera = nullptr;

		float m_DeltaTime = 0.0f;
		int m_FPS = 0;
		int m_FrameCount = 0;
		std::chrono::steady_clock::time_point m_FrameTimer;

		float m_FrameTimeAccumulator = 0.0f;
		int m_FramesPassed = 0;

		void ResetTimer()
		{
			m_FrameTimer = std::chrono::high_resolution_clock::now();
			if (m_FrameTimeAccumulator >= 1.0f)
			{
				m_FPS = std::lerp(m_FramesPassed, 1/m_DeltaTime, 0.1f);
				m_FrameTimeAccumulator = 0;
				m_FramesPassed = 0;
			}
		}
		
		void EndFrameTimer()
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			m_DeltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime-m_FrameTimer).count()/1000.0f;
			m_FrameTimeAccumulator += m_DeltaTime;
			m_FramesPassed++;
		}
	};
}