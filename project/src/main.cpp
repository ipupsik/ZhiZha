#include <future>
#include <iostream>

#include "utils.h"
#include "SystemManager.h"
#include "Systems.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

using namespace sf::Extensions::Vector2;

int main() {
	auto window = sf::RenderWindow(sf::VideoMode(800, 600), "Sample");

	auto& sys = SystemManager::Current
	            .RegisterSystem<RenderSystem>(window, 4)
	            .RegisterSystem<TestSystem>()
	            .RegisterSystem<EventSystem>(window);

	window.setVerticalSyncEnabled(true);
	window.setActive(false);
	
	auto render = std::thread([&window, &sys] {
		sf::Clock clock{};
		window.setActive(true);
		while (window.isOpen()) {
			sys.Update();

			sys.PostUpdate();
			std::cout << "FPS: " << 1 / clock.restart().asSeconds() << "\r";
		}
		std::cout << std::endl;
		window.setActive(false);
	});

	sys.PostInit();
	render.join();
	window.setActive(true);
}
