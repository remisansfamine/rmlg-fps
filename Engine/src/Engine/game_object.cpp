#include "game_object.hpp"

#include "debug.hpp"
#include "sprite_renderer.hpp"

namespace Engine
{
	GameObject::GameObject(const std::string& name)
		: m_name(name)
	{
		Core::Debug::Log::info("Creating a GameObject named " + name);

		m_components.push_back(std::shared_ptr<Component>(new LowRenderer::SpriteRenderer()));
	}

	GameObject::~GameObject()
	{

	}

	// TODO: CALL AWAKE AT THE CORRECT TIME
	void GameObject::awakeComponents()
	{
		for (std::shared_ptr<Component> component : m_components)
			component->awake();
	}

	// TODO: CALL START AT THE CORRECT TIME
	void GameObject::startComponents()
	{
		for (std::shared_ptr<Component> component : m_components)
			component->start();
	}

	void GameObject::updateComponents()
	{
		for (std::shared_ptr<Component> component : m_components)
			component->update();
	}
}