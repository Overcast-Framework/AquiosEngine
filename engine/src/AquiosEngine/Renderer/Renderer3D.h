#pragma once
#include <glm/glm.hpp>
#include <AquiosEngine/Renderer/GPUBuffer.h>
#include <AquiosEngine/Renderer/VertexLayout.h>
#include <AquiosEngine/Renderer/Pipeline.h>

namespace Aquios
{
	// TO-DO: sort this out later, when I am gonna be doing 3D
	class Renderer3D
	{
	public:
		virtual void DrawMesh(CommandList* cmdList, Mesh* mesh) = 0;
	};
}