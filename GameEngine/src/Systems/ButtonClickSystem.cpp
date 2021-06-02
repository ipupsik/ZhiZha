#include <Components/ButtonComponent.h>
#include <SFML/Window/Mouse.hpp>
#include <Components/SpriteComponent.h>
#include "Systems/ButtonClickSystem.h"

void ButtonClickSystem::OnUpdate() {
	const auto& items = _entities->GetEntitiesBy<ButtonComponent, SpriteComponent>();

	for (auto item: items) {
		auto&[button, sprite] = item.Components;

		if (!button->Bounds.contains(sf::Mouse::getPosition(_window))) {
			sprite->Sprite->setColor(sf::Color::White);
			continue;
		}

		sprite->Sprite->setColor(sf::Color{ 144, 144, 144 });

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			button->OnClick();
	}
}

ButtonClickSystem::ButtonClickSystem(sf::Window& window)
		:_window(window) {
}
