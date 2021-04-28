#pragma once

#include "renderer.hpp"

namespace LowRenderer
{
	class ModelRenderer : public Renderer
	{
	private:
	// std::shared_ptr<Model> model = nullptr;

	public:
		void draw() override;
	};
}