#pragma once

#include "component.hpp"

namespace LowRenderer
{
	class Renderer : public Engine::Component
	{
	public:
		Renderer();

		void virtual draw() = 0;
	};
}