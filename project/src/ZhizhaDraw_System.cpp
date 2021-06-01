#include <Components/MaterialComponent.h>
#include <Components/MeshComponent.h>
#include <Components/TransformComponent.h>

#include "Components/LayerComponent.h"
#include "Components/RenderedComponent.h"
#include "ZhizhaVolumeComponent.h"
#include "GlobalRotation_Component.h"
#include "ZhizhaDraw_System.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

void ZhizhaDraw_System::OnPostUpdate() {
	const auto& items = _entities->GetEntitiesBy<MaterialComponent, ZhizhaVolumeComponent>();

	for (auto& [components, entity] : items) {
		glPushMatrix();
		auto& [material, ZhizhaVolume] = components;
		if (_entities->HasComponent<GlobalRotation_Component>(*entity))
			glRotatef(_phi, 0, 0, 1);

		glTranslatef(_camera_location.x, _camera_location.y, 0);

		glUseProgram(material->_materialId);

		//Attach all textures
		for (int i = 0; i < material->Textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, material->Textures[i]->_textureId);

			glUniform1i(glGetUniformLocation(material->_materialId, std::string("tex" + std::to_string(i)).c_str()), i);
		}
		//--

		float transMatrix[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, transMatrix);
		glm::mat4x4 ModelView = {
			glm::vec4(transMatrix[0], transMatrix[1], transMatrix[2], transMatrix[3]),
			glm::vec4(transMatrix[4], transMatrix[5], transMatrix[6], transMatrix[7]),
			glm::vec4(transMatrix[8], transMatrix[9], transMatrix[10], transMatrix[11]),
			glm::vec4(transMatrix[12], transMatrix[13], transMatrix[14], transMatrix[15])
		};

		GLint matrixId = glGetUniformLocation(material->_materialId, "Transform");
		glUniformMatrix4fv(matrixId, 1, GL_FALSE, glm::value_ptr(ModelView));

		if (ZhizhaVolume->vertices[ZhizhaVolume->side].size() > 0)
		{
			glBindVertexArray(ZhizhaVolume->indexVAO);
			{
				for (int i = 0; i < 1; i++)
					glEnableVertexAttribArray(i);

				{
					glBindBuffer(GL_ARRAY_BUFFER, ZhizhaVolume->indexVBO);
					{
						glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(float) * ZhizhaVolume->vertices[ZhizhaVolume->side].size(), 
							ZhizhaVolume->vertices[ZhizhaVolume->side].data(), GL_STREAM_DRAW);
					}
					glBindBuffer(GL_ARRAY_BUFFER, 0);

					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ZhizhaVolume->indexEBO);
					{
						std::vector<unsigned int> indexes;
						indexes.resize(ZhizhaVolume->vertices[ZhizhaVolume->side].size());
						for (unsigned int i = 0; i < indexes.size(); i++)
							indexes[i] = i;
						glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexes.size(), indexes.data(), GL_STREAM_DRAW);

						glDrawElements(GL_TRIANGLES, indexes.size() / 3, GL_UNSIGNED_INT, NULL);
					}
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				}

				for (int i = 0; i >= 0; i--)
					glDisableVertexAttribArray(i);
			}
			glBindVertexArray(0);
		}
		glUseProgram(0);

		ZhizhaVolume->vertices[ZhizhaVolume->side].clear();
		ZhizhaVolume->side = (ZhizhaVolume->side + 1) % 2;

		glPopMatrix();
	}
}
