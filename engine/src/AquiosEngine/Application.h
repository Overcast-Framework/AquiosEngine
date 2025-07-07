#pragma once
#include "AquiosEngine/Core.h"

namespace Aquios
{
	class AQUIOS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in the client
	Application* CreateApplication();
}

