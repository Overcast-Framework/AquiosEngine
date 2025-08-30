#pragma once
#include <AquiosEngine/Core.h>
#include <sstream>

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

	inline std::ostream& operator<<(std::ostream& os, std::shared_ptr<Event> e)
	{
		return os << e->ToString();
	}
}