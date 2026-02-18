#pragma once
#include <string>
#include <vector>
#include <AquiosEngine/EventSystem.h>

namespace Aquios
{
	template<typename T>
	class AssetLoader : IEventDispatcher
	{
	public:
		virtual T* Load(std::string source) = 0;
		virtual void Unload(T* asset) = 0;
		virtual T* Reload(T* asset) = 0;

		const std::vector<T*>& GetLoadedAssets() const { return LoadedAssets; }
	private:
		std::vector<T*> LoadedAssets;
	};
}