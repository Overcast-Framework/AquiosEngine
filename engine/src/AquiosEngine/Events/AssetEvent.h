#pragma once
#include <AquiosEngine/Events/Event.h>
#include <AquiosEngine/Assets/Asset.h>

namespace Aquios
{
	class AssetLoadedEvent : public Event
	{
	public:
		const char* GetName() const override
		{
			return "AssetLoadedEvent";
		}

		std::string ToString() const override
		{
			return "AssetLoadedEvent";
		}

		Asset* GetAsset() { return m_Asset; }
	private:
		Asset* m_Asset;
	};

	class AssetUnloadedEvent : public Event
	{
	public:
		const char* GetName() const override
		{
			return "AssetUnloadedEvent";
		}

		std::string ToString() const override
		{
			return "AssetUnloadedEvent";
		}

		Asset* GetAsset() { return m_Asset; }
	private:
		Asset* m_Asset;
	};

	class AssetReloadedEvent : public Event
	{
	public:
		const char* GetName() const override
		{
			return "AssetReloadedEvent";
		}

		std::string ToString() const override
		{
			return "AssetReloadedEvent";
		}

		Asset* GetAsset() { return m_Asset; }
	private:
		Asset* m_Asset;
	};
}
