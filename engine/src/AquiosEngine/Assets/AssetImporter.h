#pragma once
#include <AquiosEngine/Assets/Asset.h>
#include <AquiosEngine/Assets/AssetMetadata.h>

namespace Aquios
{
	class AssetImporter
	{
		std::shared_ptr<Asset> ImportAsset(AssetHandle handle, const AssetMetadata& metadata);
	};
}