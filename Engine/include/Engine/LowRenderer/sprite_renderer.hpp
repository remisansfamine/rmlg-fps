#pragma once

#include "renderer.hpp"
#include "texture.hpp"
#include "mesh.hpp"

namespace LowRenderer
{
	class SpriteRenderer : public Renderer
	{
	private:
		std::shared_ptr<Resources::Mesh> mesh = nullptr;
		std::shared_ptr<Resources::Texture> texture = nullptr;
	public:
		Core::Maths::vec4 m_color = Core::Maths::vec4(1.f, 1.f, 1.f, 1.f);

		SpriteRenderer(Engine::GameObject& gameObject, const std::string& shaderPromgramName);
		SpriteRenderer(Engine::GameObject& gameObject, const std::string& shaderPromgramName, const std::string& texturePath);
		SpriteRenderer(Engine::GameObject& gameObject, const std::shared_ptr<SpriteRenderer>& ptr, const std::string& shaderPromgramName);

		std::string getTexturePath();

		void draw() const override;
		void drawImGui() override;
		std::string toString() const override;

		static void parseComponent(Engine::GameObject& gameObject, std::istringstream& iss);
	};
}