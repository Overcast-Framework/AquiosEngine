#include <aqpch.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "OpenGLContext.h"

namespace Aquios::OpenGL
{
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(this->m_WindowHandle);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AQ_CORE_ASSERT(status, "couldn't initialize GLAD");
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(this->m_WindowHandle);
	}
}