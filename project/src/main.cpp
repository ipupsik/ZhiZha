#include <iostream>

#include "Components.h"
#include "EntityManager.h"
#include "utils.h"
#include "SystemManager.h"
#include "Systems.h"
#include "SFML/Graphics/RenderWindow.hpp"

using namespace sf::Extensions::Vector2;

int main() {
	auto window = sf::RenderWindow(sf::VideoMode(800, 600), "Sample");

	auto& sys = SystemManager::Current
	            .RegisterSystem<EventSystem>(window)
	            .RegisterSystem<RenderSystem>(window, 4)
	            .RegisterSystem<TestSystem>();

	sf::Clock clock{};

	window.setVerticalSyncEnabled(true);
	sys.PostInit();
	while (window.isOpen()) {
		sys.Update();

		sys.PostUpdate();
		std::cout << "FPS: " << 1 / clock.restart().asSeconds() << "\r";
	}
	std::cout << std::endl;
}
