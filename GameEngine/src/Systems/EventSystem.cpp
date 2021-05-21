#include "Systems/EventSystem.h"

#include "SFML/Window/Event.hpp"

void EventSystem::OnPostInit() {
	sf::Event event{};

	while (_window.isOpen())
		if (_window.waitEvent(event) && event.type == sf::Event::Closed)
			_window.close();
}
