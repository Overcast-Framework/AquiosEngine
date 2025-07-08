#pragma once
#include <AquiosEngine/Events/Event.h>

namespace Aquios
{
	class AQUIOS_API WindowEvent : public Event
	{
	public:
		WindowEvent()
		{
		}

		const char* GetName() const override
		{
			return "WindowEvent";
		}

		std::string ToString() const override
		{
			return "WindowEvent";
		}
	};

	class AQUIOS_API WindowResizeEvent : public WindowEvent
	{
	public:
		inline int GetNewWidth() const { return m_Width; }
		inline int GetNewHeight() const { return m_Height; }

		WindowResizeEvent(int w, int h) : m_Width(w), m_Height(h)
		{
		}

		const char* GetName() const override
		{
			return "WindowResizeEvent";
		}

		std::string ToString() const override
		{
			std::ostringstream oss;
			oss << "WindowResizeEvent(" << m_Width << "; " << m_Height << ")";
			return oss.str();
		}
	private:
		int m_Width, m_Height;
	};

	class AQUIOS_API WindowCloseEvent : public WindowEvent
	{
	public:
		WindowCloseEvent()
		{
		}

		const char* GetName() const override
		{
			return "WindowResizeEvent";
		}

		std::string ToString() const override
		{
			std::ostringstream oss;
			oss << "WindowCloseEvent";
			return oss.str();
		}
	};

	class AQUIOS_API WindowFocusEvent : public WindowEvent // im gonna want to add the window class to these later maybe
	{
	public:
		WindowFocusEvent()
		{
		}

		const char* GetName() const override
		{
			return "WindowFocusEvent";
		}

		std::string ToString() const override
		{
			std::ostringstream oss;
			oss << "WindowFocusEvent";
			return oss.str();
		}
	};

	class AQUIOS_API WindowLostFocusEvent : public WindowEvent
	{
	public:
		WindowLostFocusEvent()
		{
		}

		const char* GetName() const override
		{
			return "WindowLostFocusEvent";
		}

		std::string ToString() const override
		{
			std::ostringstream oss;
			oss << "WindowLostFocusEvent";
			return oss.str();
		}
	};

	class AQUIOS_API WindowMovedEvent : public WindowEvent
	{
	public:
		inline int GetX() const { return m_X; }
		inline int GetY() const { return m_Y; }

		WindowMovedEvent(int x, int y) : m_X(x), m_Y(y)
		{
		}

		const char* GetName() const override
		{
			return "WindowLostFocusEvent";
		}

		std::string ToString() const override
		{
			std::ostringstream oss;
			oss << "WindowLostFocusEvent";
			return oss.str();
		}
	private:
		int m_X, m_Y;
	};
}