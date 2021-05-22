#include <iostream>
#include "Systems/EventSystem.h"

#include "SFML/Window/Event.hpp"

void EventSystem::OnPostInit() {
	sf::Event event{};

	while (_window.isOpen()) {
		if (_window.waitEvent(event)) {
			if (event.type == sf::Event::Closed)
				_window.close();
			if (event.type == sf::Event::Resized) {
				auto view = _window.getView();
				view.setSize(event.size.width, event.size.height);
				view.setCenter(event.size.width / 2.f, event.size.height / 2.f);
				_window.setView(view);
			}
			if (event.type == sf::Event::MouseWheelScrolled) {
				auto view = _window.getView();
				std::cout << event.mouseWheelScroll.delta << std::endl;
				view.zoom(event.mouseWheelScroll.delta / 2 + 1);
				view.setCenter(event.mouseWheelScroll.x, event.mouseWheelScroll.y);
				_window.setView(view);
			}
		}
	}
}
