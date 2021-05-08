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
	_window.clear(sf::Color{
		static_cast<sf::Uint8>(rand() % 256), static_cast<sf::Uint8>(rand() % 256), static_cast<sf::Uint8>(rand() % 256)
	});
	_window.display();
}
