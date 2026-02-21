#include "aqpch.h"
#include "OpenGLPipeline.h"
#include "OpenGLShader.h"

void Aquios::OpenGL::OpenGLPipeline::Bind(CommandList* list)
{
	list->Record(Commands::BindPipelineCmd(this));
}

void Aquios::OpenGL::OpenGLPipeline::Release()
{
	glDeleteProgram(this->m_ProgramId);
}

void Aquios::OpenGL::OpenGLPipeline::Build()
{
	switch (this->m_PipelineSpec->Type)
	{
		case PipelineType::Graphics:
		{
			GraphicsPipelineSpec* graphicsSpec = (GraphicsPipelineSpec*)this->m_PipelineSpec;

			if (!graphicsSpec) {
				AQ_CORE_FATAL("[OPENGL]", "Failed to cast PipelineSpec* to GraphicsPipelineSpec*");
				return;
			}

			OpenGLShader* vShader = (OpenGLShader*)graphicsSpec->VertexShader.get();
			OpenGLShader* fShader = (OpenGLShader*)graphicsSpec->FragmentShader.get();

			if (!vShader || !fShader) {
				AQ_CORE_ERROR("[OPENGL]", "Shader pointers are null");
				return;
			}

			this->m_ProgramId = glCreateProgram();

			glAttachShader(this->m_ProgramId, vShader->GetShaderId());
			glAttachShader(this->m_ProgramId, fShader->GetShaderId());

			glLinkProgram(this->m_ProgramId);

			int success;
			char infoLog[512];

			glGetProgramiv(this->m_ProgramId, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(this->m_ProgramId, 512, NULL, infoLog);
				AQ_CORE_ERROR("[OPENGL]", infoLog);
			}

			glValidateProgram(this->m_ProgramId);
			GLint valid;
			glGetProgramiv(this->m_ProgramId, GL_VALIDATE_STATUS, &valid);
			if (!valid) {
				GLint logLength;
				glGetProgramiv(this->m_ProgramId, GL_INFO_LOG_LENGTH, &logLength);
				std::vector<char> infoLog(logLength);
				glGetProgramInfoLog(this->m_ProgramId, logLength, NULL, infoLog.data());
				AQ_CORE_ERROR("[OPENGL]", infoLog.data());
			}

			AQ_CORE_ASSERT(success, "[OPENGL]", "Program couldn't be linked");
		}
	}
}
