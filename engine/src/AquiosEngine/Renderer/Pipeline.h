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
		Shader* VertexShader;
		Shader* FragmentShader;
		Shader* ComputeShader;

		VertexLayout* VertexLayout;
		PipelineSettings Settings;
		PipelineType Type;
	};

	class Pipeline : public IDestructable
	{
	public:
		virtual void Bind(CommandList* list) = 0;
		PipelineSpec& GetSpec() { return m_PipelineSpec; }

		virtual void Release() = 0;

		virtual ~Pipeline() = default;
	protected:
		PipelineSpec m_PipelineSpec;
	};
}