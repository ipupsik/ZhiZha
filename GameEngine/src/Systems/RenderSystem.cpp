#include <Components/MaterialComponent.h>
#include <Components/MeshComponent.h>
#include <Components/TransformComponent.h>
#include "Systems/RenderSystem.h"

#include "Components/LayerComponent.h"
#include "Components/RenderedComponent.h"
#include "GlobalRotation_Component.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

void RenderSystem::OnPostUpdate() {
	const auto& items = _entities->GetEntitiesBy<LayerComponent>();

	for (const auto& item : items) {
		_window.setView(_views.at(std::get<0>(item.Components)->Index));
		drawWithOpenGl(item);
		drawWithSFML(item);
	}
}

void RenderSystem::drawWithOpenGl(const ComplexComponent<LayerComponent>& item) {
	auto material = _entities->GetComponent<MaterialComponent>(*item.Entity);
	auto mesh = _entities->GetComponent<MeshComponent>(*item.Entity);
	auto transform = _entities->GetComponent<TransformComponent>(*item.Entity);

	if (material == nullptr || mesh == nullptr || transform == nullptr)
		return;

	glPushMatrix();
	if (_entities->HasComponent<GlobalRotation_Component>(*item.Entity))
		glRotatef(_phi, 0, 0, 1);

	glTranslatef(_camera_location.x, _camera_location.y, 0);
	glUseProgram(material->_materialId);

	//Attach all textures
	for (int i = 0; i < material->Textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, material->Textures[i]->TextureId);

		glUniform1i(glGetUniformLocation(material->_materialId,
				std::string("tex" + std::to_string(i)).c_str()), i);
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
	while (TmpParent) {
		glPushMatrix();
		{
			glTranslatef(TmpParent->Location.x, TmpParent->Location.y, 0);

			glScalef(TmpParent->Scale.x, TmpParent->Scale.y, 1);
			glRotatef(TmpParent->Angle, 0, 0, 1);
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

	glPopMatrix();
}

void RenderSystem::drawWithSFML(const ComplexComponent<LayerComponent>& item) {
	auto render = _entities->GetComponent<RenderedComponent>(*item.Entity);
	auto transform = _entities->GetComponent<TransformComponent>(*item.Entity);

	if (render == nullptr) return;

	sf::RenderStates states = sf::RenderStates::Default;
	if (transform != nullptr)
		states.transform.translate(transform->Location)
				.scale(transform->Scale)
				.rotate(transform->Angle);
	_window.draw(*render->DrawableObj, states);
}
