#pragma once
#include <AquiosEngine/Platform/OpenGL/Utils.h>
#include <AquiosEngine/Renderer/Shader.h>

namespace Aquios::OpenGL
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(ShaderType type, std::string shaderSource);
		void Release() override;

		const GLid& GetShaderId() const { return m_ShaderId; }
	private:
		GLid m_ShaderId;
	};
}

