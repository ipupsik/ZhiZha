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
			GLuint VertexIndex;
			glGenBuffers(1, &VertexIndex);
			glBindBuffer(GL_ARRAY_BUFFER, VertexIndex);
			{
				glBufferData(GL_ARRAY_BUFFER,  2 * sizeof(float) * vertices.size(), &*vertices.begin(), GL_STREAM_DRAW);
				{
					glDrawArrays(GL_TRIANGLES, NULL, vertices.size());
				}
			}
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		for (int i = material->attributesCount - 1; i >= 0; i--)
			glDisableVertexAttribArray(i);
	}
	//glBindVertexArray(0);
	//--

	//Disable our shaders
	glUseProgram(0);
}