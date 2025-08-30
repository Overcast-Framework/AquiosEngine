#pragma once

namespace Aquios
{
	class IDestructable
	{
	public:
		virtual void Release() = 0;
		virtual ~IDestructable() = default;
	};
}