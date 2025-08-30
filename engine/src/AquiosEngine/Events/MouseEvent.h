#pragma once
#include <AquiosEngine/Events/Event.h>

namespace Aquios
{
	class AQUIOS_API MouseEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }

		MouseEvent(int button) : m_Button(button)
		{
		}

		const char* GetName() const override
		{
			return "MouseEvent";
		}

		std::string ToString() const override
		{
			return "MouseEvent(button " + std::to_string(m_Button) + ")";
		}

		int m_Button;
	};

	class AQUIOS_API MousePressedEvent : public MouseEvent
	{
	public:
		inline int GetRepeatCount() const { return m_RepeatCount; }

		MousePressedEvent(int button, int repeatCount) : MouseEvent(button), m_RepeatCount(repeatCount)
		{
		}

		const char* GetName() const override
		{
			return "MousePressedEvent";
		}

		std::string ToString() const override
		{
			return "MousePressedEvent(button " + std::to_string(m_Button) + "; repeated " + std::to_string(m_RepeatCount) + " times)";
		}

	private:
		int m_RepeatCount;
	};

	class AQUIOS_API MouseReleasedEvent : public MouseEvent
	{
	public:
		MouseReleasedEvent(int button) : MouseEvent(button)
		{
		}

		const char* GetName() const override
		{
			return "MouseReleasedEvent";
		}

		std::string ToString() const override
		{
			return "MouseReleasedEvent(button " + std::to_string(m_Button) + ")";
		}
	};

	class AQUIOS_API MouseMoveEvent : public MouseEvent
	{
	public:
		MouseMoveEvent(int x, int y) : MouseEvent(0), m_X(x), m_Y(y)
		{
		}

		inline int GetX() const { return m_X; }
		inline int GetY() const { return m_Y; }

		const char* GetName() const override
		{
			return "MouseMoveEvent";
		}

		std::string ToString() const override
		{
			std::ostringstream oss;
			oss << "MouseMoveEvent(" << m_X << "; " << m_Y << ")";
			return oss.str();
		}
	private:
		int m_X, m_Y;
	};

	class AQUIOS_API MouseScrollEvent : public MouseEvent
	{
	public:
		MouseScrollEvent(int x, int y) : MouseEvent(0), m_X(x), m_Y(y)
		{
		}

		inline int GetX() const { return m_X; }
		inline int GetY() const { return m_Y; }

		const char* GetName() const override
		{
			return "MouseScrollEvent";
		}

		std::string ToString() const override
		{
			std::ostringstream oss;
			oss << "MouseScrollEvent(" << m_X << "; " << m_Y << ")";
			return oss.str();
		}
	private:
		int m_X, m_Y;
	};
}