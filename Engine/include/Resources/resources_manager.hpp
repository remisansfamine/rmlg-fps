#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "singleton.hpp"
#include "shader.hpp"


namespace Resources
{
	class ResourcesManager final : public Singleton<ResourcesManager>
	{
		friend Singleton<ResourcesManager>;

	private:
		bool initialized = false;

		ResourcesManager();
		~ResourcesManager();

		std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> shaderPrograms;
		std::unordered_map<std::string, std::shared_ptr<Shader>>		shaders;

	public:
		static void init();

		static std::shared_ptr<Shader> loadShader(const std::string& shaderPath);
		static std::shared_ptr<ShaderProgram> loadShaderProgram(const std::string& programName, const std::string& vertPath = "", const std::string& fragPath = "");
	};
}