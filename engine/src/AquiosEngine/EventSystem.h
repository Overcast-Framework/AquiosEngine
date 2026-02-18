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

	class LambdaListener : public IEventListener
	{
	public:
		LambdaListener(std::function<void(std::shared_ptr<Event>)> cb) : m_Callback(std::move(cb)) {}
		void OnEvent(std::shared_ptr<Event> event) override { m_Callback(event); }
	private:
		std::function<void(std::shared_ptr<Event>)> m_Callback;
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

		template<typename T>
		std::shared_ptr<LambdaListener> Subscribe(std::function<void(std::shared_ptr<Event>)> callback)
		{
			static_assert(std::is_base_of<Event, T>::value, "T must be derived from Event");
			auto ptr = std::make_unique<LambdaListener>(callback);
			auto raw = ptr.get();

			m_LambdaStorage.push_back(std::move(ptr));
			m_Subscribers[std::type_index(typeid(T))].push_back(raw);

			return ptr;
		}

		// override if needed
		virtual void OnEvent(std::shared_ptr<Event> event) {}

		virtual ~IEventDispatcher() = default;
	private:
		std::vector<std::unique_ptr<IEventListener>> m_LambdaStorage;
		std::unordered_map<std::type_index, std::vector<std::shared_ptr<IEventListener>>> m_Subscribers;
	};
}