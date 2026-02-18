#pragma once
#include <cstdint>
#include <AquiosEngine/Renderer/Format.h>
#include <glad/glad.h>

typedef unsigned int GLid;

namespace Aquios::OpenGL
{
	inline GLuint format_to_gl(Format format)
	{
		switch (format)
		{
		case Format::Float:
			return GL_FLOAT;
		case Format::Float2:
			return GL_FLOAT;
		case Format::Float3:
			return GL_FLOAT;
		}
	}
}