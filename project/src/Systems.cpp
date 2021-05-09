#include "Systems.h"

#include "SFML/Window/Event.hpp"

void TestSystem::OnFixedUpdate() {
	_latestColor.r = (_latestColor.r + static_cast<sf::Uint8>(-(_step / 2) + rand() % _step)) % 256;
	_latestColor.b = (_latestColor.b + static_cast<sf::Uint8>(-(_step / 2) + rand() % _step)) % 256;
	_latestColor.g = (_latestColor.g + static_cast<sf::Uint8>(-(_step / 2) + rand() % _step)) % 256;

	_entities.GetComponent<RenderComponent>(_canvas)->get().color = _latestColor;
}

void EventSystem::OnPostInit() {
	sf::Event event{};

	while (_window.isOpen())
		while (_window.pollEvent(event))
			if (event.type == sf::Event::Closed) _window.close();
}

void RenderSystem::OnPostUpdate() {
	const auto entities = _entities.GetEntitiesBy<RenderComponent>();
	const Entity* canvas = nullptr;

	for (const auto& item : entities)
		if (_entities.HasComponent<NameComponent>(item) && _entities.GetComponent<NameComponent>(item)->get().Name ==
			"Canvas")
			canvas = &item;

	if (canvas == nullptr)
		return;

	_window.clear(_entities.GetComponent<RenderComponent>(*canvas)->get().color);
	_window.display();
}
