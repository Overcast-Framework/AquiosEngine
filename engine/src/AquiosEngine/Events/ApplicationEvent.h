#pragma once
#include <AquiosEngine/Events/Event.h>

namespace Aquios
{
	class AQUIOS_API AppEvent : public Event
	{
	public:
		const char* GetName() const override
		{
			return "AppEvent";
		}

		std::string ToString() const override
		{
			return "AppEvent";
		}
	protected:
		AppEvent() = default;
	};

	class AQUIOS_API AppTickEvent : public AppEvent
	{
	public:
		const char* GetName() const override
		{
			return "AppTickEvent";
		}

		std::string ToString() const override
		{
			return "AppTickEvent";
		}
	};

	class AQUIOS_API AppUpdateEvent : public AppEvent
	{
	public:
		AppUpdateEvent(float dt) : m_DeltaTime(dt)
		{
		}

		inline float GetDeltaTime() const { return m_DeltaTime; }

		const char* GetName() const override
		{
			return "AppUpdateEvent";
		}

		std::string ToString() const override
		{
			return "AppUpdateEvent(dt " + std::to_string(m_DeltaTime) + ")";
		}
	private:
		float m_DeltaTime;
	};

	class AQUIOS_API AppRenderEvent : public AppEvent
	{
	public:
		AppRenderEvent(float dt) : m_DeltaTime(dt)
		{
		}

		inline float GetDeltaTime() const { return m_DeltaTime; }

		const char* GetName() const override
		{
			return "AppRenderEvent";
		}

		std::string ToString() const override
		{
			return "AppRenderEvent(dt " + std::to_string(m_DeltaTime) + ")";
		}
	private:
		float m_DeltaTime;
	};
}