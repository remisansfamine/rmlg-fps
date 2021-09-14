#pragma once

#include <vector>
#include <string>

#include <glad\glad.h>

#include "maths.hpp"

#include "resource.hpp"

namespace Resources
{
	class Mesh : public Resource
	{
	private:
		GLuint VAO;

		void mainThreadInitialization() override;

	public:
		~Mesh();


		std::vector<float> attributs;

		void draw() const;
		void generateVAO();
		void compute(std::vector<Core::Maths::vec3>& vertices, std::vector<Core::Maths::vec3>& texCoords, std::vector<Core::Maths::vec3>& normals, std::vector<unsigned int>& indices);
	};
}
