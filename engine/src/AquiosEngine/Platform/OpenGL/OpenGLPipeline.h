#pragma once
#include <AquiosEngine/Renderer/Pipeline.h>
#include <AquiosEngine/Platform/OpenGL/Utils.h>

namespace Aquios::OpenGL
{
	class OpenGLPipeline : public Pipeline
	{
	public:
		void Bind(CommandList* list) override;

		void Release() override;

		OpenGLPipeline(const PipelineSpec* spec) : Pipeline(spec) { this->Build(); }

		OpenGLPipeline() = delete;
		OpenGLPipeline(const OpenGLPipeline&) = delete;
		OpenGLPipeline(OpenGLPipeline&&) = delete;

		const GLid& GetProgramId() const { return m_ProgramId; }
	private:
		GLid m_ProgramId;
	protected:
		void Build() override;
	};
}