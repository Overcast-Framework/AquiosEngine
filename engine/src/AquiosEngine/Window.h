#pragma once
#include <GLFW/glfw3.h>
#include <AquiosEngine/EventSystem.h>
#include <AquiosEngine/Events/WindowEvent.h>

namespace Aquios
{
	struct AQUIOS_API WindowProperties
	{
		std::string Title = "AquiosEngine";
		unsigned int Width = 1280;
		unsigned int Height = 720;
	};

	class AQUIOS_API Window : public IEventDispatcher
	{
	public:
		using EventCallbackFn = std::function<void(std::shared_ptr<Event>)>;
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		virtual ~Window() = default;
		Window() = default;

		Window(const WindowData& data) : m_Data(data)
		{
		}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		void SetEventCallback(const EventCallbackFn& callback) { m_EventCallback = callback; }
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetWindowHandle() const = 0;

		static Window* Create(const WindowProperties& properties = WindowProperties());

		WindowData m_Data;
	private:
		void OnEvent(std::shared_ptr<Event> e) override
		{
			if (m_EventCallback)
				m_EventCallback(e);
		}
	private:
		EventCallbackFn m_EventCallback;
	};
}