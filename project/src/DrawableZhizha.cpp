#include <iostream>
#include "glad/glad.h"
#include "DrawableZhizha.h"
#include "SFML/Graphics.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

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

	//--
	//glBindVertexArray(mesh->Mesh->_indexVAO);
	{
		for (int i = 0; i < material->attributesCount; i++)
			glEnableVertexAttribArray(i);

		{
			if (vertices.size() > 0)
			{
				glEnableClientState(GL_VERTEX_ARRAY);
				{
					std::vector<float>tmp = vertices;
					glVertexPointer(2, GL_FLOAT, 0, tmp.begin()._Ptr);
					{
						int length = tmp.size() / 6;
						//glDrawArrays(GL_TRIANGLES, 0, length);  <-- FIX ME
					}
				}
			}
		}

		for (int i = material->attributesCount - 1; i >= 0; i--)
			glDisableVertexAttribArray(i);
	}
	//glBindVertexArray(0);
	//--

	//Disable our shaders
	glUseProgram(0);
}