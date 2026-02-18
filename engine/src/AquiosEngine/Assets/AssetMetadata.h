#pragma once
#include <string>
#include <filesystem>
#include <AquiosEngine/Assets/Asset.h>

namespace Aquios
{
	struct AssetMetadata
	{
		AssetType Type = AssetType::None;
		std::filesystem::path FilePath;

		operator bool() const { return Type != AssetType::None; }
	};
}