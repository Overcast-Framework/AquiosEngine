#include <aqpch.h>
#include <AquiosEngine/Application.h>
#include <AquiosEngine/Platform/Windows/WindowsWindow.h>
#include <GLFW/glfw3.h>

#include "WindowsInput.h"

namespace Aquios
{
	Input* Input::s_Instance;

	bool WindowsInput::Impl_IsKeyPressed(int keycode)
	{
		auto activeWindow = dynamic_cast<Windows::WindowsWindow*>(&Application::Get().GetActiveWindow());
		if (glfwGetKey((GLFWwindow*)activeWindow->GetWindowHandle(), keycode) == GLFW_PRESS)
			return true;
		return false;
	}

	bool WindowsInput::Impl_IsMouseButtonPressed(int button)
	{
		auto activeWindow = dynamic_cast<Windows::WindowsWindow*>(&Application::Get().GetActiveWindow());
		if (glfwGetMouseButton((GLFWwindow*)activeWindow->GetWindowHandle(), button) == GLFW_PRESS)
			return true;
		return false;
	}

	std::pair<float, float> WindowsInput::Impl_GetMousePosition()
	{
		auto activeWindow = dynamic_cast<Windows::WindowsWindow*>(&Application::Get().GetActiveWindow());

		double xp, yp;
		glfwGetCursorPos((GLFWwindow*)activeWindow->GetWindowHandle(), &xp, &yp);

		return std::make_pair<float, float>(xp, yp);
	}

	float WindowsInput::Impl_GetMouseX()
	{
		auto activeWindow = dynamic_cast<Windows::WindowsWindow*>(&Application::Get().GetActiveWindow());
		double xp, yp;
		glfwGetCursorPos((GLFWwindow*)activeWindow->GetWindowHandle(), &xp, &yp);

		return xp;
	}

	float WindowsInput::Impl_GetMouseY()
	{
		auto activeWindow = dynamic_cast<Windows::WindowsWindow*>(&Application::Get().GetActiveWindow());
		double xp, yp;
		glfwGetCursorPos((GLFWwindow*)activeWindow->GetWindowHandle(), &xp, &yp);

		return yp;
	}

#ifdef AQ_PLATFORM_WINDOWS
	void Input::Init()
	{
		AQ_CORE_ASSERT(!s_Instance, "Input is already initialized");
		s_Instance = new WindowsInput();
	}
#endif
}