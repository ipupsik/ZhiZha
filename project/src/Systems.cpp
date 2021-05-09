#include "Systems.h"

#include <iostream>
#include <thread>

#include "SFML/Window/Event.hpp"

void TestSystem::OnUpdate() {
}

void TestSystem::OnPostInit() {
	std::cout << "Hello!" << std::endl;
}

void EventSystem::OnUpdate() {
	sf::Event event{};
	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			_window.close();
	}
}

void RenderSystem::OnPostUpdate() {
	_latestColor.r = (_latestColor.r + static_cast<sf::Uint8>(-(_step / 2) + rand() % _step)) % 256;
	_latestColor.b = (_latestColor.b + static_cast<sf::Uint8>(-(_step / 2) + rand() % _step)) % 256;
	_latestColor.g = (_latestColor.g + static_cast<sf::Uint8>(-(_step / 2) + rand() % _step)) % 256;
	
	_window.clear(_latestColor);
	_window.display();
}
