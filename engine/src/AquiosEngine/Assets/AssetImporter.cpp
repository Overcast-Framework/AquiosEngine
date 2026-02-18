#include "aqpch.h"
#include "AssetImporter.h"
#include <map>

namespace Aquios
{
    using ImporterFunction = std::function<std::shared_ptr<Asset>(AssetHandle, const AssetMetadata&)>;

    static std::map<AssetType, ImporterFunction> s_ImportFunctions = {

    };

    std::shared_ptr<Asset> AssetImporter::ImportAsset(AssetHandle handle, const AssetMetadata& metadata)
    {
        if (s_ImportFunctions.find(metadata.Type) == s_ImportFunctions.end())
        {
            AQ_CORE_ERROR("Couldn't find importer for type {}", AssetTypeToString(metadata.Type));
            return nullptr;
        }

        return s_ImportFunctions.at(metadata.Type)(handle, metadata);
    }
}
