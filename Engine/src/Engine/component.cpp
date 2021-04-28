#include "component.hpp"

namespace Engine
{
	void Component::setActive(bool value)
	{
		if (isActive() != value)
			value ? onEnable() : onDisable();

		Object::setActive(value);
	}

	void Component::destroy()
	{

	}
}