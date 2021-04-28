#pragma once

#include <vector>
#include <string>
#include <memory>

#include "object.hpp"
#include "component.hpp"

namespace Engine
{
	class GameObject : public Object
	{
	private:
	public:
		bool isStatic = false;
		std::string m_name;
		std::vector<std::shared_ptr<Component>> m_components;

		GameObject(const std::string& name);
		~GameObject();

		//void callColisions(Collider);
		void awakeComponents();
		void startComponents();
		void updateComponents();

		void destroy() override {}
	};
}