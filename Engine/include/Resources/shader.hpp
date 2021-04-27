#pragma once

#include <iostream>
#include <glad/glad.h>

namespace Resources
{
	struct Uniform
	{
		GLint  location;
		GLenum type;
	};

	class Shader
	{
	private:
		std::string loadFromFile(const std::string& filePath);

	public:
		GLint shaderID = GL_INVALID_VALUE;

		Shader(const std::string& shaderPath);
	};

	class ShaderProgram
	{
	private:
		GLint programID = GL_INVALID_VALUE;

		std::unordered_map<std::string, Uniform> uniforms;

	public:
		ShaderProgram(const std::string& programName, const std::string& vertPath, const std::string& fragPath);
	};
}