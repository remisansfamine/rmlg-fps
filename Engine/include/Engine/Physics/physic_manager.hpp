#pragma once
#include "singleton.hpp"

namespace Physics
{
	class PhysicManager final : public Singleton<PhysicManager>
	{
		friend Singleton<PhysicManager>;

	private:
		PhysicManager();
		~PhysicManager();

	public:
		static void clearColliders() { PhysicManager* test = instance(); }
	};
}