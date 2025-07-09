#pragma once

#include <GLFW/glfw3.h>
#include <AquiosEngine/Layer.h>
#include <AquiosEngine/Events/KeyEvent.h>
#include <AquiosEngine/Events/MouseEvent.h>

namespace Aquios
{
	class AQUIOS_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(std::shared_ptr<Event>& e);
	private:
		float m_Time = 0.0f;
	};
}