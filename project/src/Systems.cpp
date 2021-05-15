#include "Systems.h"
#include "SFML/Window/Event.hpp"

#ifdef linux

#include <cmath>
#include <iostream>

constexpr auto PI = M_PI;
#elif defined(_WIN32) || defined(WIN32) || defined(__WIN32)
constexpr auto PI = 3.141592653589793238462643383279502884;
#endif

void TestSystem::OnFixedUpdate() {
    sf::Color color{};
    color.r = 256 * std::abs(sin(_x += _step));
    color.g = 256 * std::abs(sin((_x += _step) + PI / 3));
    color.b = 256 * std::abs(sin((_x += _step) + 2 * PI / 3));

    _entities.GetComponent<RenderComponent>(_canvas)->color = color;

    if (_x == 100)
        _x = 0;
}

void EventSystem::OnPostInit() {
    sf::Event event{};

    while (_window.isOpen())
        while (_window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                _window.close();
}

void RenderSystem::OnPostUpdate() {
    auto entities = _entities.GetEntitiesBy<RenderComponent>();
    const RenderComponent *canvas = nullptr;

    for (const auto& item : entities)
        if (_entities.HasComponent<NameComponent>(item->GetEntity()) &&
            _entities.GetComponent<NameComponent>(item->GetEntity())->Name == "Canvas")
            canvas = item;

    if (canvas == nullptr)
        return;

    _window.clear(canvas->color);
    _window.display();
}

void HugeSystem::OnUpdate() {
	auto test = _entities.GetEntitiesBy<HugeComponent>();
	for (const auto& entity: test)
		entity->Index;
}

void HugeSystem::OnInit() {
	auto& parent = _entities.CreateEntity();
	_entities.GetOrAddComponent<HugeComponent>(parent);

	for (std::size_t i = 0; i < _count; i++) {
		auto& entity = _entities.Instantiate(parent);
		_entities.GetComponent<HugeComponent>(entity)->Index = i;
	}
}
