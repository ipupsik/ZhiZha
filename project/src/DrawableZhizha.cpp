#include <iostream>
#include "glad/glad.h"
#include "DrawableZhizha.h"
#include "SFML/Graphics.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

void DrawableZhizha::initMesh() {
	glGenBuffers(1, &indexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, indexVBO);
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(sf::Vector2f) * vertices[side].size(), vertices[side].begin()._Ptr, GL_DYNAMIC_DRAW);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sf::Vector2f) * vertices[side].size(), vertices[side].begin()._Ptr, GL_DYNAMIC_DRAW);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &indexVAO);
	glBindVertexArray(indexVAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, indexVBO);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);
}

void DrawableZhizha::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	glUseProgram(material->_materialId);

	//Attach all textures
	for (int i = 0; i < material->Textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, material->Textures[i]->_textureId);

		glUniform1i(glGetUniformLocation(material->_materialId, std::string("tex" + std::to_string(i)).c_str()), i);
	}
	//--

	if (vertices[side].size() > 0)
	{
		glBindVertexArray(indexVAO);
		{
			for (int i = 0; i < 1; i++)
				glEnableVertexAttribArray(i);

			{
				glBindBuffer(GL_ARRAY_BUFFER, indexVBO);
				{
					glBufferData(GL_ARRAY_BUFFER, sizeof(sf::Vector2f) * vertices[side].size(), vertices[side].begin()._Ptr, GL_STREAM_DRAW);
				}
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexEBO);
				{
					std::vector<unsigned int> indexes;
					indexes.resize(vertices[side].size());
					for (unsigned int i = 0; i < indexes.size(); i++)
						indexes[i] = i;
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexes.size(), indexes.begin()._Ptr, GL_STREAM_DRAW);

					glDrawElements(GL_TRIANGLES, indexes.size() / 3, GL_UNSIGNED_INT, NULL);
				}
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}

			for (int i = 0; i >= 0; i--)
				glDisableVertexAttribArray(i);
		}
		glBindVertexArray(0);
	}
	//--

	//Disable our shaders
	glUseProgram(0);
}