#pragma once
#include <AquiosEngine/Assets/Asset.h>
#include <string>

namespace Aquios
{
	class ShaderAsset : public Asset
	{
	public:
		enum class AShaderType
		{
			Vertex, Fragment,
			Compute, Geometry,
			Mesh, Hit, Miss
		} Type;

		std::string SourceCode;

		ShaderAsset(const std::string& src, AShaderType type) : Asset(src, LoadedFrom::File)
		{
			Type = type;
		}
	};
}