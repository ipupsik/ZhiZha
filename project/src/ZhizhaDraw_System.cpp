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

	glPushMatrix();
	glTranslatef(_camera_location.x, _camera_location.y, 0);

	for (auto& [components, entity] : items) {
		glPushMatrix();
		auto& [material, ZhizhaVolume] = components;
		if (_entities->HasComponent<GlobalRotation_Component>(*entity))
			glRotatef(_phi, 0, 0, 1);

		glUseProgram(material->_materialId);

		//Attach all textures
		for (int i = 0; i < material->Textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, material->Textures[i]->_textureId);

			glUniform1i(glGetUniformLocation(material->_materialId, std::string("tex" + std::to_string(i)).c_str()), i);
		}
		//--

		if (ZhizhaVolume->vertices[ZhizhaVolume->side].size() > 0)
		{
			glBindVertexArray(ZhizhaVolume->indexVAO);
			{
				for (int i = 0; i < 1; i++)
					glEnableVertexAttribArray(i);

				{
					glBindBuffer(GL_ARRAY_BUFFER, ZhizhaVolume->indexVBO);
					{
						glBufferData(GL_ARRAY_BUFFER, sizeof(sf::Vector2f) * ZhizhaVolume->vertices[ZhizhaVolume->side].size(), 
							ZhizhaVolume->vertices[ZhizhaVolume->side].begin()._Ptr, GL_STREAM_DRAW);
					}
					glBindBuffer(GL_ARRAY_BUFFER, 0);

					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ZhizhaVolume->indexEBO);
					{
						std::vector<unsigned int> indexes;
						indexes.resize(ZhizhaVolume->vertices[ZhizhaVolume->side].size());
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
		glUseProgram(0);
	}
	glPopMatrix();
}
