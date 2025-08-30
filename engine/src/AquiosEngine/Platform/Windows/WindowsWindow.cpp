#include "aqpch.h"
#include "WindowsWindow.h"

#include <AquiosEngine/Platform/OpenGL/OpenGLContext.h>

bool Aquios::Windows::WindowsWindow::s_IsGLFWInitialized;

Aquios::Windows::WindowsWindow::WindowsWindow(const WindowData& data) : Window(data)
{
    if (!s_IsGLFWInitialized)
    {
        int success = glfwInit();
        AQ_CORE_ASSERT(success, "couldn't initialize GLFW");
        s_IsGLFWInitialized = success;
    }

    this->m_WindowHandle = glfwCreateWindow(data.Width, data.Height, data.Title.c_str(), nullptr, nullptr);

    m_Context = new OpenGL::OpenGLContext(m_WindowHandle);
    m_Context->Init();

    glfwSetWindowUserPointer(this->m_WindowHandle, this);
    SetVSync(true);

    glfwSetWindowSizeCallback(this->m_WindowHandle, 
        [](GLFWwindow* m_Window, int width, int height) -> void
        {
            auto* self = static_cast<Aquios::Window*>(glfwGetWindowUserPointer(m_Window));
            AQ_CORE_ASSERT(self != nullptr, "could not get window from user ptr");
            self->m_Data.Width = width;
            self->m_Data.Height = height;
            self->SendEvent<WindowResizeEvent>(std::make_shared<WindowResizeEvent>(self, width, height));
        }
    );

    glfwSetWindowFocusCallback(this->m_WindowHandle, 
        [](GLFWwindow* m_Window, int focused) -> void
        {
            auto* self = static_cast<Aquios::Window*>(glfwGetWindowUserPointer(m_Window));
            AQ_CORE_ASSERT(self != nullptr, "could not get window from user ptr");

            if(focused)
                self->SendEvent<WindowFocusEvent>(std::make_shared<WindowFocusEvent>(self));
            else
                self->SendEvent<WindowLostFocusEvent>(std::make_shared<WindowLostFocusEvent>(self));
        });

    glfwSetCursorPosCallback(this->m_WindowHandle, [](GLFWwindow* m_Window, double x, double y) -> void
        {
            auto* self = static_cast<Aquios::Window*>(glfwGetWindowUserPointer(m_Window));
            AQ_CORE_ASSERT(self != nullptr, "could not get window from user ptr");

            self->SendEvent<MouseMoveEvent>(std::make_shared<MouseMoveEvent>((int)x, (int)y));
        });

    glfwSetScrollCallback(this->m_WindowHandle, [](GLFWwindow* m_Window, double x, double y) -> void
        {
            auto* self = static_cast<Aquios::Window*>(glfwGetWindowUserPointer(m_Window));
            AQ_CORE_ASSERT(self != nullptr, "could not get window from user ptr");

            self->SendEvent<MouseScrollEvent>(std::make_shared<MouseScrollEvent>((int)x, (int)y));
        });
    
    glfwSetKeyCallback(this->m_WindowHandle, [](GLFWwindow* m_Window, int key, int scancode, int action, int mods) -> void
        {
            auto* self = static_cast<Aquios::Window*>(glfwGetWindowUserPointer(m_Window));
            AQ_CORE_ASSERT(self != nullptr, "could not get window from user ptr");

            if (action == GLFW_PRESS || action == GLFW_REPEAT)
                self->SendEvent<KeyPressedEvent>(std::make_shared<KeyPressedEvent>(key, 0));
            else
                self->SendEvent<KeyReleasedEvent>(std::make_shared<KeyReleasedEvent>(key));
        });

    glfwSetCharCallback(this->m_WindowHandle, [](GLFWwindow* m_Window, unsigned int codepoint) -> void
        {
            auto* self = static_cast<Aquios::Window*>(glfwGetWindowUserPointer(m_Window));
            AQ_CORE_ASSERT(self != nullptr, "could not get window from user ptr");

            self->SendEvent<TextInputEvent>(std::make_shared<TextInputEvent>(codepoint));
        });

    glfwSetMouseButtonCallback(this->m_WindowHandle, [](GLFWwindow* m_Window, int btn, int action, int mods) -> void
        {
            auto* self = static_cast<Aquios::Window*>(glfwGetWindowUserPointer(m_Window));
            AQ_CORE_ASSERT(self != nullptr, "could not get window from user ptr");

            if (action == GLFW_PRESS)
                self->SendEvent<MousePressedEvent>(std::make_shared<MousePressedEvent>(btn, 0));
            else
                self->SendEvent<MouseReleasedEvent>(std::make_shared<MouseReleasedEvent>(btn));
        });
}

Aquios::Windows::WindowsWindow::~WindowsWindow()
{
    glfwTerminate();
}

HWND Aquios::Windows::WindowsWindow::GetWin32Handle()
{
    return glfwGetWin32Window(this->m_WindowHandle);
}

void Aquios::Windows::WindowsWindow::OnUpdate()
{
    if (glfwWindowShouldClose(this->m_WindowHandle))
    {
        this->SendEvent<WindowCloseEvent>(std::make_shared<WindowCloseEvent>(this));
    }

    glfwPollEvents();
    m_Context->SwapBuffers();
}

unsigned int Aquios::Windows::WindowsWindow::GetWidth() const
{
    return this->m_Data.Width;
}

unsigned int Aquios::Windows::WindowsWindow::GetHeight() const
{
    return this->m_Data.Height;
}

void Aquios::Windows::WindowsWindow::SetVSync(bool enabled)
{
    this->m_Data.VSync = enabled;
    glfwSwapInterval(enabled ? 1 : 0);
}

bool Aquios::Windows::WindowsWindow::IsVSync() const
{
    return this->m_Data.VSync;
}

#ifdef AQ_PLATFORM_WINDOWS
namespace Aquios
{
    Window* Window::Create(const WindowProperties& props)
    {
        WindowData winData{ props.Title, props.Width, props.Height };
        Windows::WindowsWindow* win_window = new Windows::WindowsWindow(winData);

        AQ_CORE_INFO("Created Window '{0}' ({1}x{2})", props.Title, props.Width, props.Height);

        return win_window;
    }
}
#endif