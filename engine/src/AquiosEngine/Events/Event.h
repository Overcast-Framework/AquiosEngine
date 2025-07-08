#pragma once
#include <AquiosEngine/Core.h>

namespace Aquios
{
	class AQUIOS_API Event
	{
	public:
		bool IsHandled = false;

		virtual ~Event() = default;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const = 0;
	};
}