#include "material.hpp"

#include <imgui.h>

#include "resources_manager.hpp"
#include "utils.hpp"
#include "maths.hpp"

namespace Resources
{
	std::shared_ptr<Material> Material::defaultMaterial = nullptr;

	Material::Material(const std::string& name)
		: Resource(name)
	{

	}

	void Material::sendToShader(const std::shared_ptr<ShaderProgram>& shaderProgram) const
	{
		// Set the model's material informations 
		shaderProgram->setUniform("material.ambient", &ambient);
		shaderProgram->setUniform("material.diffuse", &diffuse);
		shaderProgram->setUniform("material.specular", &specular);
		shaderProgram->setUniform("material.emissive", &emissive);
		
		shaderProgram->setUniform("material.shininess", &shininess);

		// Set the textures' location of the shader program
		std::vector<std::string> shaderName =
		{ "material.alphaTexture", "material.ambientTexture", "material.diffuseTexture",
			"material.emissiveTexture", "material.specularTexture"};

		for (int i = 0; i < 5; i++)
			shaderProgram->setUniform(shaderName[i], &i);
	}

	void Material::bindTextures() const
	{
		if (alphaTex)
			if (!alphaTex->bind(0))
				Texture::defaultAlpha->bind(0);

		if (ambientTex)
			if (!ambientTex->bind(1))
				Texture::defaultAmbient->bind(1);

		if (diffuseTex)
			if (!diffuseTex->bind(2))
				Texture::defaultDiffuse->bind(2);
			
		if (emissiveTex)
			if (!emissiveTex->bind(3))
				Texture::defaultEmissive->bind(3);

		if (specularTex)
			if (!specularTex->bind(4))
				Texture::defaultSpecular->bind(4);

		glActiveTexture(0);
	}

	void Material::drawImGui()
	{
		if (ImGui::TreeNode(m_filePath.c_str()))
		{
			if (ImGui::TreeNode("Alpha texture:"))
			{
				alphaTex->drawImGui();
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Ambient texture:"))
			{
				ambientTex->drawImGui();
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Diffuse texture:"))
			{
				diffuseTex->drawImGui();
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Emissive texture:"))
			{
				emissiveTex->drawImGui();
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Specular texture:"))
			{
				specularTex->drawImGui();
				ImGui::TreePop();
			}

			ImGui::TreePop();
		}
	}

	LowRenderer::Color getColor(std::istringstream& iss)
	{
		// Get a Color data form string stream
		LowRenderer::Color color = { 0.f };

		iss >> color.data.r;
		iss >> color.data.g;
		iss >> color.data.b;

		return color;
	}

	void Material::parse(const std::string& toParse, const std::string& directoryPath)
	{
		std::istringstream stringStream(toParse);

		std::string line;
		while (std::getline(stringStream, line))
		{
			std::istringstream iss(line);
			std::string type;
			iss >> type;

			if (type == "#" || type == "" || type == "\n" || type == "n")
				continue;

			if (type == "Ns")
			{
				iss >> shininess;
				continue;
			}
			if (type == "Ka")
			{
				ambient = getColor(iss);
				continue;
			}
			if (type == "Kd")
			{
				diffuse = getColor(iss);
				continue;
			}
			if (type == "Ks")
			{
				specular = getColor(iss);
				continue;
			}
			if (type == "Ke")
			{
				emissive = getColor(iss);
				continue;
			}
			if (type == "Ni")
			{
				iss >> opticalDensity;
				continue;
			}
			if (type == "d")
			{
				iss >> transparency;
				continue;
			}
			if (type == "illum")
			{
				iss >> illumination;
				continue;
			}

			std::string texName;
			iss >> texName;

			std::shared_ptr<Texture>* texturePtr;

			// Load mesh textures
			if (type == "map_Ka")
				texturePtr = &ambientTex;
			else if (type == "map_Kd")
				texturePtr = &diffuseTex;
			else if (type == "map_Ks")
				texturePtr = &specularTex;
			else if (type == "map_Ke")
				texturePtr = &emissiveTex;
			else if (type == "map_d")
				texturePtr = &alphaTex;
			else
				continue;

			*texturePtr = ResourcesManager::loadTexture(directoryPath + Utils::getFileNameFromPath(texName));
		}
	}
}