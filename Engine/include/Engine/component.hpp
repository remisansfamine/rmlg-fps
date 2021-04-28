#pragma once

#include "object.hpp"

//#include "game_object.hpp"

namespace Engine
{
	class Component : public Object
	{
		//friend class GameObject;

	public:
		//GameObject& gameObject;
		//Trasnform& transform;

		void setActive(bool value) override;
		void destroy() override;

		void virtual awake() { };
		void virtual start() { };
		void virtual update() { };
		void virtual fixedUpdate() { };
		void virtual lateUpdate() { };
		void virtual onEnable() { };
		void virtual onDisable() { };

		// TODO: Add collision and trigger functions
		//void virtual onCollisions()

	public:
		Component() {}
		~Component() {}
	};
}