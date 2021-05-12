#include "Systems.h"

#include "SFML/Window/Event.hpp"

constexpr auto M_PI = 3.141592653589793238462643383279502884;

void TestSystem::OnFixedUpdate() {
	sf::Color color{};
	color.r = 256 * std::abs(sin(_x += _step));
	color.g = 256 * std::abs(sin((_x += _step) + M_PI / 3));
	color.b = 256 * std::abs(sin((_x += _step) + 2 * M_PI / 3));
	
	_entities.GetComponent<RenderComponent>(_canvas)->color = color;

	if (_x == 100)
		_x = 0;
}

void EventSystem::OnPostInit() {
	sf::Event event{};

	while (_window.isOpen())
		if (_window.waitEvent(event) && event.type == sf::Event::Closed)
			_window.close();
}

void RenderSystem::OnPostUpdate() {
	auto entities = _entities.GetEntitiesBy<RenderComponent>();
	const Entity* canvas = nullptr;

	for (const auto& item : entities)
		if (_entities.HasComponent<NameComponent>(item) &&
			_entities.GetComponent<NameComponent>(item)->Name == "Canvas")
			canvas = &item;

	if (canvas == nullptr)
		return;

	_window.clear(_entities.GetComponent<RenderComponent>(*canvas)->color);
	_window.display();
}
