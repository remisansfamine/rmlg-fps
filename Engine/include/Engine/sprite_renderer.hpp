#pragma once

#include "renderer.hpp"

namespace LowRenderer
{
	class SpriteRenderer : public Renderer
	{
	private:
	// std::shared_ptr<Texture> texture = nullptr;
		

	public:
		void draw() override;
		void update() override;
	};
}