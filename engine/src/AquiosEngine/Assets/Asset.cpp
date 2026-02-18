#include "aqpch.h"
#include "Asset.h"

std::string_view Aquios::AssetTypeToString(AssetType type)
{
	switch (type)
	{
		case AssetType::None:		return "AssetType::None";
		case AssetType::Scene:		return "AssetType::Scene";
		case AssetType::Texture:	return "AssetType::Texture";
		case AssetType::Shader:		return "AssetType::Shader";
		case AssetType::Model:		return "AssetType::Model";
		case AssetType::Sound:		return "AssetType::Sound";
	}

	return "AssetType::<Invalid>";
}

Aquios::AssetType Aquios::AssetTypeFromString(std::string_view assetType)
{
	if (assetType == "AssetType::None")     return AssetType::None;
	if (assetType == "AssetType::Scene")    return AssetType::Scene;
	if (assetType == "AssetType::Texture")	return AssetType::Texture;
	if (assetType == "AssetType::Shader")	return AssetType::Shader;
	if (assetType == "AssetType::Model")	return AssetType::Model;
	if (assetType == "AssetType::Sound")	return AssetType::Sound;

	return AssetType::None;
}
