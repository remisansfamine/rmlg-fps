#include "resources_manager.hpp"

#include "debug.hpp"

namespace Resources
{
	ResourcesManager::ResourcesManager()
	{
		Core::Debug::Log::logInfo("Creating the Resources Manager");
	}

	ResourcesManager::~ResourcesManager()
	{
		Core::Debug::Log::logInfo("Destroying the Resources Manager");
	}

	void ResourcesManager::init()
	{
		ResourcesManager* RM = instance();

		if (RM->initialized)
		{
			Core::Debug::Log::logError("The Resources Manager is already initialized");
			return;
		}

		// TODO : Add basic materials/models/textures

		RM->initialized = true;

		Core::Debug::Log::logInfo("Resources Manager initialized");
	}

	std::shared_ptr<Shader> ResourcesManager::loadShader(const std::string& shaderPath)
	{
		ResourcesManager* RM = instance();
		
		const auto& shaderIt = RM->shaders.find(shaderPath);

		if (shaderIt != RM->shaders.end())
		{
			return shaderIt->second;
		}

		// TODO: Add Warn load fail
		return RM->shaders[shaderPath] = std::make_shared<Shader>(Shader(shaderPath));
	}

	std::shared_ptr<ShaderProgram> ResourcesManager::loadShaderProgram(const std::string& programName, const std::string& vertPath, const std::string& fragPath)
	{
		ResourcesManager* RM = instance();

		const auto& programIt = RM->shaderPrograms.find(programName);

		if (programIt != RM->shaderPrograms.end())
		{
			return programIt->second;
		}

		// TODO: Add Warn load fail
		return RM->shaderPrograms[programName] = std::make_shared<ShaderProgram>(ShaderProgram(programName, vertPath, fragPath));
	}
}