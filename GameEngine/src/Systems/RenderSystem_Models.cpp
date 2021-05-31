#include <Components/MaterialComponent.h>
#include <Components/MeshComponent.h>
#include <Components/TransformComponent.h>
#include "Systems/RenderSystem_Models.h"

#include "Components/LayerComponent.h"
#include "Components/RenderedComponent.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

void RenderSystem_Models::OnPostUpdate() {
	const auto& items = _entities->GetEntitiesBy<MaterialComponent, MeshComponent, TransformComponent>();

	glPushMatrix();
	glTranslatef(_camera_location.x, _camera_location.y, 0);
	glRotatef(_phi, 1, 0, 0);
	for (auto& [components, entity] : items) {
		auto& [material, mesh, transform] = components;

		glUseProgram(material->_materialId);

		//Attach all textures
		for (int i = 0; i < material->Textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, material->Textures[i]->_textureId);

			glUniform1i(glGetUniformLocation(material->_materialId, std::string("tex" + std::to_string(i)).c_str()), i);
		}
		//--

			//Find transform matrix on world coords
		glm::mat4x4 result(
			glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
			glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
			glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		);
		const TransformComponent* TmpParent = transform;
		while (TmpParent)
		{
			glPushMatrix();
			{
				glTranslatef(TmpParent->Location.x, TmpParent->Location.y, 0);

				glScalef(TmpParent->Scale.x, TmpParent->Scale.y, 1);
				glRotatef(TmpParent->Angle, 1, 0, 0);

				float transMatrix[16];
				glGetFloatv(GL_MODELVIEW_MATRIX, transMatrix);
				glm::mat4x4 ModelView = {
					glm::vec4(transMatrix[0], transMatrix[1], transMatrix[2], transMatrix[3]),
					glm::vec4(transMatrix[4], transMatrix[5], transMatrix[6], transMatrix[7]),
					glm::vec4(transMatrix[8], transMatrix[9], transMatrix[10], transMatrix[11]),
					glm::vec4(transMatrix[12], transMatrix[13], transMatrix[14], transMatrix[15])
				};

				result = ModelView * result;
			}
			glPopMatrix();

			TmpParent = TmpParent->parent;
		}

		//--

		//Bind all out buffers to draw primitives
		GLint matrixId = glGetUniformLocation(material->_materialId, "Transform");
		glUniformMatrix4fv(matrixId, 1, GL_FALSE, glm::value_ptr(result));

		glBindVertexArray(mesh->Mesh->_indexVAO);
		{
			for (int i = 0; i < material->attributesCount; i++)
				glEnableVertexAttribArray(i);

			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->Mesh->_indexEBO);
				{
					glDrawElements(GL_TRIANGLES, 3 * mesh->Mesh->_faces.size(), GL_UNSIGNED_INT, NULL);
				}
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}

			for (int i = material->attributesCount - 1; i >= 0; i--)
				glDisableVertexAttribArray(i);
		}
		glBindVertexArray(0);
		//--

		//Disable our shaders
		glUseProgram(0);
	}

	glPopMatrix();
}
