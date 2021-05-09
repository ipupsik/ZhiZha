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
		.RegisterSystem<RenderSystem>(window)
		.RegisterSystem<TestSystem>(4)
		.RegisterSystem<EventSystem>(window);

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

	auto physic = std::thread([&window, &sys] {
		sf::Clock deltaClock;
		const sf::Time fixedDelta = sf::seconds(1.0f / 60);
		sf::Time sinceUpdate = sf::Time::Zero;

		while (window.isOpen()) {
			sinceUpdate += deltaClock.restart();

			if (sinceUpdate > fixedDelta) {
				sinceUpdate -= fixedDelta;
				sys.FixedUpdate();
			}
		}
	});

	sys.PostInit();
	render.join();
	window.setActive(true);
	physic.join();
}
