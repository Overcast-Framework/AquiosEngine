#pragma once
#include <AquiosEngine/Events/Event.h>

namespace Aquios
{
	class IEventListener
	{
	public:
		virtual ~IEventListener() = default;
		virtual void OnEvent(std::shared_ptr<Event> event) = 0;
	};

	class IEventDispatcher : public IEventListener
	{
	public:
		template<typename T>
		void SendEvent(const std::shared_ptr<T>& event)
		{
			static_assert(std::is_base_of<Event, T>::value, "T must be derived from Event");
			for (auto& listener : m_Subscribers[std::type_index(typeid(T))])
			{
				listener->OnEvent(event);
				if (dynamic_cast<Event*>(event.get())->IsHandled)
					break;
			}
		}
		template<typename T>
		void Subscribe(IEventListener* listener)
		{
			static_assert(std::is_base_of<Event, T>::value, "T must be derived from Event");
			m_Subscribers[std::type_index(typeid(T))].emplace_back(listener);
		}

		// override if needed
		virtual void OnEvent(std::shared_ptr<Event> event) {}

		virtual ~IEventDispatcher() = default;
	private:
		std::unordered_map<std::type_index, std::vector<IEventListener*>> m_Subscribers;
	};
}