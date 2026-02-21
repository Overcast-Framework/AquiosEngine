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
		case Format::RGB8:
			return GL_RGB8;
		case Format::RGBA8:
			return GL_RGBA8;
		case Format::D24S8:
			return GL_DEPTH24_STENCIL8;
		}
	}
}