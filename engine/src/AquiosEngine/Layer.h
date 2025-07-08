#pragma once

#include <AquiosEngine/Core.h>
#include <AquiosEngine/Events/Event.h>
#include <AquiosEngine/EventSystem.h>

namespace Aquios
{
	class AQUIOS_API Layer : IEventDispatcher
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(std::shared_ptr<Event>& e) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}