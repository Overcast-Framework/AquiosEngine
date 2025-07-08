#pragma once
#include <glad/glad.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <AquiosEngine/EventSystem.h>
#include <AquiosEngine/Events/WindowEvent.h>
#include <AquiosEngine/Events/MouseEvent.h>
#include <AquiosEngine/Events/KeyEvent.h>
#include <AquiosEngine/Events/ApplicationEvent.h>
#include <AquiosEngine/Window.h>
#include <AquiosEngine/Log.h>

namespace Aquios::Windows
{
	class AQUIOS_API WindowsWindow : public Window
	{
	public:
		WindowsWindow() = default;
		WindowsWindow(const WindowData& data);

		~WindowsWindow();

		HWND GetWin32Handle();
		void OnUpdate() override;

		unsigned int GetWidth() const override;
		unsigned int GetHeight() const override;

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
	private:
		GLFWwindow* m_WindowHandle = nullptr;
		static bool s_IsGLFWInitialized;
	};
}