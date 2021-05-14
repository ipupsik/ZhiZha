#include "Systems.h"
#include "SFML/Window/Event.hpp"

#ifdef linux

#include <cmath>

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
    const Entity *canvas = nullptr;

    for (const auto& item : entities)
        if (_entities.HasComponent<NameComponent>(item) &&
            _entities.GetComponent<NameComponent>(item)->Name == "Canvas")
            canvas = &item;

    if (canvas == nullptr)
        return;

    _window.clear(_entities.GetComponent<RenderComponent>(*canvas)->color);
    _window.display();
}
