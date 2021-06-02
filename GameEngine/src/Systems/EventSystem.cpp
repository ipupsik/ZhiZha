#include "Systems/EventSystem.h"

#include "SFML/Window/Event.hpp"

void EventSystem::OnPostInit() {
	sf::Event event{};

	while (_window.isOpen() && _engine.IsActive()) {
		if (_window.waitEvent(event)) {
			if (event.type == sf::Event::Closed)
				_window.close();
			if (event.type == sf::Event::Resized) {
				_gameView.setSize(event.size.width, event.size.height);
				_gameView.setCenter(event.size.width / 2.f, event.size.height / 2.f);
			}
			if (event.type == sf::Event::MouseWheelScrolled) {
				_gameView.zoom(event.mouseWheelScroll.delta / 2 + 1);
				_gameView.setCenter(event.mouseWheelScroll.x, event.mouseWheelScroll.y);
			}
		}
	}
}
