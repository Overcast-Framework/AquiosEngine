#include "aqpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

Aquios::OpenGL::OpenGLShader::OpenGLShader(ShaderType type, std::string shaderSource)
{
	this->Type = type;
	switch (this->Type)
	{
	case ShaderType::Vertex:
		this->m_ShaderId = glCreateShader(GL_VERTEX_SHADER);
		break;
	case ShaderType::Fragment:
		this->m_ShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case ShaderType::Compute:
		this->m_ShaderId = glCreateShader(GL_COMPUTE_SHADER);
		break;
	}

	const char* ccShaderSrc = shaderSource.c_str();
	glShaderSource(this->m_ShaderId, 1, &ccShaderSrc, NULL);
	glCompileShader(this->m_ShaderId);

	int success;
	char infoLog[512];
	glGetShaderiv(this->m_ShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(this->m_ShaderId, 512, NULL, infoLog);
		AQ_CORE_ERROR("[OpenGL]: Failed to compile shader | {0}", infoLog);
	}
}

void Aquios::OpenGL::OpenGLShader::Release()
{
	glDeleteShader(this->m_ShaderId);
}
