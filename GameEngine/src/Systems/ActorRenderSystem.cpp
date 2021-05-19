#include "Systems/ActorRenderSystem.h"
#include "Components/ActorComponent.h"
#include "Components/MaterialComponent.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

void ActorRenderSystem::OnPostUpdate()
{
	auto entities = _entities->GetEntitiesBy<ActorComponent>();

	glBegin(GL_TRIANGLES);
	glVertex3f(0, 0, 0); glVertex3f(0, 1, 0); glVertex3f(0, 1, 1);
	glEnd();

	for (const auto& [Components, Entity] : entities)
	{
		//Gettings Components
		auto [Actor] = Components;

		//Active out shaders
		glUseProgram(Actor->Material._materialId);

		//Attach all textures
		for (int i = 0; i < Actor->Material.Textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, Actor->Material.Textures[i]->_textureId);

			glUniform1i(glGetUniformLocation(Actor->Material._materialId, std::string("tex" + std::to_string(i)).c_str()), i);
		}
		//--

		//Find transform matrix on world coords
		ActorComponent* parent = &*Actor;
		glm::mat4x4 result;

		while (parent)
		{
			glPushMatrix();
			{
				glTranslatef(Actor->Transform.Location.x, Actor->Transform.Location.y, 0);

				glScalef(Actor->Transform.Scale.x, Actor->Transform.Scale.y, 1);
				glRotatef(Actor->Transform.Rotation.x, 1, 0, 0);

				float transMatrix[16];
				glGetFloatv(GL_MODELVIEW_MATRIX, transMatrix);
				glm::mat4x4 ModelView = {
					glm::vec4(transMatrix[0], transMatrix[1], transMatrix[2], transMatrix[3]),
					glm::vec4(transMatrix[4], transMatrix[5], transMatrix[6], transMatrix[7]),
					glm::vec4(transMatrix[8], transMatrix[9], transMatrix[10], transMatrix[11]),
					glm::vec4(transMatrix[12], transMatrix[13], transMatrix[14], transMatrix[15])
				};

				result = ModelView * result;
				parent = parent->parent;
			}
			glPopMatrix();
		}
		//--

		//Bind all out buffers to draw primitives
		GLint matrixId = glGetUniformLocation(Actor->Material._materialId, "Transform");
		glUniformMatrix4fv(matrixId, 1, GL_FALSE, glm::value_ptr(result));

		glBindVertexArray(Actor->Mesh->_indexVAO);
		{
			for (int i = 0; i < Actor->Material.attributesCount; i++)
				glEnableVertexAttribArray(i);

			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Actor->Mesh->_indexEBO);
				{
					glDrawElements(GL_TRIANGLES, 3 * Actor->Mesh->_faces.size(), GL_UNSIGNED_INT, NULL);
				}
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}

			for (int i = Actor->Material.attributesCount - 1; i >= 0; i--)
				glDisableVertexAttribArray(i);
		}
		glBindVertexArray(0);
		//--

		//Disable our shaders
		glUseProgram(0);
	}
}