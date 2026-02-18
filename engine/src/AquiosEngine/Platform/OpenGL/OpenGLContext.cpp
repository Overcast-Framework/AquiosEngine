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

		int flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

			glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
				AQ_CORE_WARN("[OPENGL/DBG] Source {} Severity {} Type {} || {}", source, severity, type, message);
				}, nullptr);
		}
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(this->m_WindowHandle);
	}
}