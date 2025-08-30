#pragma once
#include <AquiosEngine/Input.h>

namespace Aquios
{
	class AQUIOS_API WindowsInput : public Input
	{
	public:
		bool Impl_IsKeyPressed(int keycode) override;
		bool Impl_IsMouseButtonPressed(int keycode) override;
		std::pair<float, float> Impl_GetMousePosition() override;
		float Impl_GetMouseX() override;
		float Impl_GetMouseY() override;
	};
}