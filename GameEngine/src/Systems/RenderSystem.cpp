#include <Components/MaterialComponent.h>
#include <Components/MeshComponent.h>
#include <Components/TransformComponent.h>
#include "Systems/RenderSystem.h"

#include "Components/LayerComponent.h"
#include "Components/RenderedComponent.h"

void RenderSystem::OnPostUpdate() {
	const auto& items = _entities->GetEntitiesBy<RenderedComponent, LayerComponent>();

	for (auto&[components, entity]: items) {
		auto&[render, layer] = components;
		sf::RenderStates states = sf::RenderStates::Default;
		_window.setView(_views.at(layer->Index));
		_window.draw(*render->DrawableObj, states);
	}
}
