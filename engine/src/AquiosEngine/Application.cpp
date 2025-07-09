#include "aqpch.h"
#include "Application.h"
#include <AquiosEngine/Events/WindowEvent.h>
#include <AquiosEngine/Events/MouseEvent.h>
#include <AquiosEngine/Events/KeyEvent.h>
#include <AquiosEngine/Events/ApplicationEvent.h>
#include <AquiosEngine/Log.h>
#include <glad/glad.h>

namespace Aquios
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		AQ_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());

		m_Window->Subscribe<WindowCloseEvent>(this);
		m_Window->Subscribe<WindowResizeEvent>(this);
		m_Window->Subscribe<WindowFocusEvent>(this);
		m_Window->Subscribe<WindowLostFocusEvent>(this);
		m_Window->Subscribe<MouseMoveEvent>(this);
		m_Window->Subscribe<MousePressedEvent>(this);
		m_Window->Subscribe<MouseReleasedEvent>(this);
		m_Window->Subscribe<MouseScrollEvent>(this);
		m_Window->Subscribe<TextInputEvent>(this);
		m_Window->Subscribe<KeyPressedEvent>(this);
		m_Window->Subscribe<KeyReleasedEvent>(this);
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(std::shared_ptr<Event> event)
	{
		if (dynamic_cast<WindowCloseEvent*>(event.get()))
		{
			m_Running = false;
		}

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(event);
			if (event->IsHandled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::Run()
	{
		m_Running = true;

		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}
}
