#pragma once
#include <AquiosEngine/UUID.h>

namespace Aquios
{
	using AssetHandle = UUID;

	enum class AssetType : uint16_t
	{
		None = 0, Shader, Texture,
		Sound, Scene,
		Model
	};

	std::string_view AssetTypeToString(AssetType type);
	AssetType AssetTypeFromString(std::string_view assetType);

	class Asset
	{
	public:
		Asset() 
			: m_AssetId(AssetHandle()) 
		{
		}

		virtual AssetType GetAssetType() const = 0;
		const AssetHandle& GetAssetId() const { return m_AssetId; }
	private:
		AssetHandle m_AssetId;
	};
}