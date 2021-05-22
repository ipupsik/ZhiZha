#include <Components/MaterialComponent.h>
#include <Components/MeshComponent.h>
#include <Components/TransformComponent.h>
#include "Systems/RenderSystem.h"

void RenderSystem::OnPostUpdate() {
	const auto& items = _entities->GetEntitiesBy<MeshComponent>();

	for (auto&[components, entity]: items) {
		auto&[render] = components;

		auto texture = _entities->GetComponent<MaterialComponent>(*entity);
		auto transform = _entities->GetComponent<TransformComponent>(*entity);
		sf::RenderStates states(sf::BlendMultiply);
		sf::Transform transf;
		if (texture != nullptr) {
			states.shader = texture->Shader;
			states.texture = texture->Texture;
		}
		if (transform != nullptr) {
			transf.translate(transform->Location)
					.scale(transform->Scale)
					.rotate(transform->Angle);
			states.transform = transf;
		}
		_window.draw(*render->Buffer, states);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render->Elements);
		glDrawElements(GL_TRIANGLES, 3 * render->FacesSize, GL_UNSIGNED_INT, nullptr);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
