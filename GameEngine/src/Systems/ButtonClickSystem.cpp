#include <Components/ButtonComponent.h>
#include <SFML/Window/Mouse.hpp>
#include <Components/SpriteComponent.h>
#include "Systems/ButtonClickSystem.h"

void ButtonClickSystem::OnUpdate() {
	const auto& items = _entities->GetEntitiesBy<ButtonComponent>();

	for (auto item: items) {
		auto&[button] = item.Components;

		if (!button->Bounds.contains(sf::Mouse::getPosition(_window))) {
			button->OnHoverEnds();
			continue;
		}

		button->OnHover();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			button->OnClick();
	}
}

ButtonClickSystem::ButtonClickSystem(sf::Window& window)
		:_window(window) {
}
