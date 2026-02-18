#pragma once
#include <glm/glm.hpp>

#define VERTEXFPOS(x, y, z) Aquios::Vertex({x,y,z}, {0,0,-1}, {0,0,0}, {0,0,0}, {0,0})
#define VERTEXFPOS_TEX(x, y, z, u, v) Aquios::Vertex({x,y,z}, {0,0,-1}, {0,0,0}, {0,0,0}, {u, v})

namespace Aquios
{
	struct Vertex
	{
	public:
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec3 Tangent;
		glm::vec3 Bitangent;
		glm::vec2 TexCoord;

		Vertex(const glm::vec3& Position, const glm::vec3& Normal, const glm::vec3& Tangent, const glm::vec3& Bitangent, const glm::vec2& TexCoord)
			: Position(Position), Normal(Normal), Tangent(Tangent), Bitangent(Bitangent), TexCoord(TexCoord)
		{
		}
	};
}