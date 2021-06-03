#include "Systems/EventSystem.h"

#include "SFML/Window/Event.hpp"

void EventSystem::OnPostInit() {
	sf::Event event{};

	while (_window.isOpen() && _engine.IsActive()) {
		if (_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				_window.close();
		}
	}
}
