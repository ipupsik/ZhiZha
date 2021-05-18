#include "Systems.h"
#include "SFML/Window/Event.hpp"

#ifdef linux

#include <cmath>

constexpr auto PI = M_PI;
#elif defined(_WIN32) || defined(WIN32) || defined(__WIN32)
constexpr auto PI = 3.141592653589793238462643383279502884;
#endif

void EventSystem::OnPostInit() {
    sf::Event event{};

    while (_window.isOpen())
        while (_window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                _window.close();
}

void RenderSystem::OnPostUpdate() {
    auto items = _entities->GetEntitiesBy<RenderComponent, NameComponent>();
    const RenderComponent *canvas = nullptr;

    for (const auto& [Components, Entity] : items) {
	    if (auto [render, name] = Components; name->Name == "Canvas")
			canvas = render;
	}

    if (canvas == nullptr)
        return;

    _window.clear(canvas->color);
    _window.display();
}