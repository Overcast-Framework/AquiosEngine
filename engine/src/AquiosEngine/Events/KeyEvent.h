#include <AquiosEngine/Events/Event.h>

namespace Aquios
{
	class AQUIOS_API KeyEvent : public Event
	{
	public:
		inline int GetKeycode() const { return m_KeyCode; }

		KeyEvent(int keycode) : m_KeyCode(keycode)
		{
		}

		const char* GetName() const override
		{
			return "KeyEvent";
		}

		std::string ToString() const override
		{
			return "KeyEvent(keycode " + std::to_string(m_KeyCode)+")";
		}
		
		int m_KeyCode;
	};

	class AQUIOS_API KeyPressedEvent : public KeyEvent
	{
	public:
		inline int GetRepeatCount() const { return m_RepeatCount; }

		KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount)
		{
		}

		const char* GetName() const override
		{
			return "KeyPressedEvent";
		}

		std::string ToString() const override
		{
			return "KeyPressedEvent(keycode " + std::to_string(m_KeyCode) + "; repeated " + std::to_string(m_RepeatCount) + " times)";
		}
	private:
		int m_RepeatCount;
	};

	class AQUIOS_API TextInputEvent : public KeyEvent
	{
	public:
		TextInputEvent(int keycode) : KeyEvent(keycode)
		{
		}

		const char* GetName() const override
		{
			return "TextInputEvent";
		}

		std::string ToString() const override
		{
			return "TextInputEvent(keycode " + std::to_string(m_KeyCode) + ")";
		}
	private:
	};

	class AQUIOS_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode)
		{
		}

		const char* GetName() const override
		{
			return "KeyReleasedEvent";
		}

		std::string ToString() const override
		{
			return "KeyReleasedEvent(keycode " + std::to_string(m_KeyCode) + ")";
		}
	};
}