#pragma once
#include <AquiosEngine/Renderer/GraphicsContext.h>
#include <glad/glad.h>

struct GLFWwindow;

namespace Aquios::OpenGL
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {};

		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}