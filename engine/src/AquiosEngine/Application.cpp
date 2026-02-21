#include "aqpch.h"
#include "Application.h"
#include <AquiosEngine/Events/WindowEvent.h>
#include <AquiosEngine/Events/MouseEvent.h>
#include <AquiosEngine/Events/KeyEvent.h>
#include <AquiosEngine/Events/ApplicationEvent.h>
#include <AquiosEngine/Log.h>
#include <AquiosEngine/Input.h>
#include <glad/glad.h>

namespace Aquios
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		AQ_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_ActiveWindow = m_Window.get();

		Input::Init();

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

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
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
		else if (auto focusEvent = dynamic_cast<WindowFocusEvent*>(event.get()))
		{
			m_ActiveWindow = &focusEvent->GetWindow();
			AQ_CORE_INFO("current active window: {0}", m_ActiveWindow->m_Data.Title);
		}
		else if (auto resizeEvent = dynamic_cast<WindowResizeEvent*>(event.get()))
		{
			m_ActiveWindow->GetRenderer()->OnResize(resizeEvent->GetNewWidth(), resizeEvent->GetNewHeight());
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
			auto* renderer = this->GetActiveWindow().GetRenderer();

			renderer->BeginFrame();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
				layer->OnRender(*renderer);
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			renderer->Stats.DrawCalls = 0;

			m_Window->OnUpdate();
		}

		glfwTerminate();
	}
}
