#pragma once
#include "AquiosEngine/Core.h"
#include <AquiosEngine/Window.h>
#include <AquiosEngine/LayerStack.h>

namespace Aquios
{
	class AQUIOS_API Application : public IEventDispatcher
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(std::shared_ptr<Event> event) override;

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static inline Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		std::unique_ptr<Window> m_Window = nullptr;
		bool m_Running = false;
		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	// To be defined in the client
	Application* CreateApplication();
}

