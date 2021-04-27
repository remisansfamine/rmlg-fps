#include <fstream>

#include "shader.hpp"
#include "debug.hpp"
#include "utils.hpp"

#include "resources_manager.hpp"

namespace Resources
{
#pragma region SHADER
	Shader::Shader(const std::string& shaderPath)
	{
		Core::Debug::Log::logInfo("Loading " + shaderPath);

        std::string codeString = loadFromFile(shaderPath);
        const char* code = codeString.c_str();

        glShaderSource(shaderID, 1, &code, NULL);
        glCompileShader(shaderID);

        // Check if the compilation is a success
        GLint success;
        GLchar infoLog[GL_INFO_LOG_LENGTH];
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(shaderID, GL_INFO_LOG_LENGTH, NULL, infoLog);
            Core::Debug::Log::logError(shaderPath + " shader compilation failed" + infoLog);
        }
	}

	std::string Shader::loadFromFile(const std::string& filePath)
	{
        std::ifstream ifs(filePath);

        // Check if the file can be read
        if (!ifs.fail())
        {
            // Create the shader by checking its extension
            if (Utils::hasSuffix(filePath, ".vert"))
                shaderID = glCreateShader(GL_VERTEX_SHADER);

            else if (Utils::hasSuffix(filePath, ".frag"))
                shaderID = glCreateShader(GL_FRAGMENT_SHADER);

            else
                Core::Debug::Log::logError("File extension is not compatible");
        }
        else
            Core::Debug::Log::logError("Cannot open the file " + filePath);

        // Send the code to OpenGL as a char*
        std::string string_code;
        string_code.assign((std::istreambuf_iterator<char>(ifs)),
            (std::istreambuf_iterator<char>()));

        return string_code;
	}
#pragma endregion


#pragma region SHADER_PROGRAM
	ShaderProgram::ShaderProgram(const std::string& programName, const std::string& vertPath, const std::string& fragPath)
        : programID(glCreateProgram())
	{
        Core::Debug::Log::logInfo("Loading program " + programName);

        Core::Debug::Log::logInfo("Linking " + vertPath + " and " + fragPath + " to " + programName);

        std::shared_ptr<Shader> vert = Resources::ResourcesManager::loadShader(vertPath);
        std::shared_ptr<Shader> frag = Resources::ResourcesManager::loadShader(fragPath);

        // TODO: Check if the shaders are valid

        // Attach the two shaders and link them
        glAttachShader(programID, vert->shaderID);
        glAttachShader(programID, frag->shaderID);

        glLinkProgram(programID);

        // Check if there is an error
        GLint success;
        GLchar infoLog[GL_INFO_LOG_LENGTH];
        glGetProgramiv(programID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(programID, GL_INFO_LOG_LENGTH, NULL, infoLog);
            Core::Debug::Log::logError(programName + " shader program linking failed" + infoLog);
        }
        // TODO: Load locations
        // If there is no error, load the uniform locations of the program
        //else
        //    loadLocations();
	}
#pragma endregion
}