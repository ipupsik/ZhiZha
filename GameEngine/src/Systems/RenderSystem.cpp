#include <Components/MaterialComponent.h>
#include <Components/MeshComponent.h>
#include <Components/TransformComponent.h>
#include "Systems/RenderSystem.h"

#include "Components/LayerComponent.h"

void RenderSystem::OnPostUpdate() {
	const auto& items = _entities->GetEntitiesBy<MeshComponent, LayerComponent>();

	for (auto&[components, entity]: items) {
		auto&[render, layer] = components;

		auto texture = _entities->GetComponent<MaterialComponent>(*entity);
		auto transform = _entities->GetComponent<TransformComponent>(*entity);
		sf::RenderStates states = sf::RenderStates::Default;
		if (texture != nullptr) {
			states.shader = texture->Shader;
			states.texture = texture->Texture;
		}
		if (transform != nullptr) {
			sf::Transform transf;
			transf.translate(transform->Location)
			      .scale(transform->Scale)
			      .rotate(transform->Angle);
			states.transform = transf;
		}
		_window.setView(_views.at(layer->Index));
		_window.draw(*render->Drawable, states);
	}
}
