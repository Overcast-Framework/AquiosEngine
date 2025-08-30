#pragma once
#include <AquiosEngine/Core.h>
#include <AquiosEngine/Window.h>

namespace Aquios
{
	class AQUIOS_API Input
	{
	public:
		static bool IsKeyPressed(int keycode) { return s_Instance->Impl_IsKeyPressed(keycode); }
		static bool IsMouseButtonPressed(int button) { return s_Instance->Impl_IsMouseButtonPressed(button); }
		static std::pair<float, float> GetMousePosition() { return s_Instance->Impl_GetMousePosition(); }
		static float GetMouseX() { return s_Instance->Impl_GetMouseX(); }
		static float GetMouseY() { return s_Instance->Impl_GetMouseY(); }

		static void Init();
	protected:
		virtual bool Impl_IsKeyPressed(int keycode) = 0;
		virtual bool Impl_IsMouseButtonPressed(int keycode) = 0;
		virtual std::pair<float, float> Impl_GetMousePosition() = 0;
		virtual float Impl_GetMouseX() = 0;
		virtual float Impl_GetMouseY() = 0;
	private:
		static Input* s_Instance;
	};
}