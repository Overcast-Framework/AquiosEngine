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

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}