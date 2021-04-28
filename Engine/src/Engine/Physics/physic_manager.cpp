#include "physic_manager.hpp"

#include "debug.hpp"

namespace Physics
{
	PhysicManager::PhysicManager()
	{
		Core::Debug::Log::info("Creating the Physic Manager");
	}

	PhysicManager::~PhysicManager()
	{
		Core::Debug::Log::info("Destroying the Physic Manager");
	}
}