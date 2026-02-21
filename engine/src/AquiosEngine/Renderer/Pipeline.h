#pragma once
#include <AquiosEngine/Renderer/VertexLayout.h>
#include <AquiosEngine/Renderer/Shader.h>
#include <AquiosEngine/IDestructable.h>
#include <AquiosEngine/Renderer/CommandList.h>

namespace Aquios
{
	struct PipelineSettings
	{
	public:
		bool DepthTest;
	};

	enum class PipelineType
	{
		Graphics, Compute
	};

	class PipelineSpec
	{
	public:
		PipelineType Type;
	};

	struct GraphicsPipelineSpec : public PipelineSpec {
		Scope<Shader> VertexShader;
		Scope<Shader> FragmentShader;
		Ref<VertexLayout> VertexLayout;
		PipelineSettings Settings;
	};

	struct ComputePipelineSpec : public PipelineSpec {
		Shader* ComputeShader;
	};

	class Pipeline : public IDestructable
	{
	public:
		virtual void Bind(CommandList* list) = 0;
		const PipelineSpec* GetSpec() { return m_PipelineSpec; }

		explicit Pipeline(const PipelineSpec* spec) : m_PipelineSpec(spec) {}

		virtual void Release() = 0;

		virtual ~Pipeline() = default;
	protected:
		const PipelineSpec* m_PipelineSpec;

		virtual void Build() = 0;
	};
}