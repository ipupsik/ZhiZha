#include <thread>
#include <iostream>

#include "utils.h"
#include "SystemManager.h"
#include "Systems.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

using namespace sf::Extensions::Vector2;

int main() {
	auto window = sf::RenderWindow(sf::VideoMode(800, 600), "Sample");
	float delta = 0;

	auto& sys = SystemManager::Current
		.RegisterSystem<RenderSystem>(window)
		.RegisterSystem<TestSystem>(0.016)
		.RegisterSystem<EventSystem>(window);

	window.setActive(false);

	auto render = std::thread([&window, &sys, &delta] {
		sf::Clock clock{};
		window.setActive(true);

		while (window.isOpen()) {
			sys.Update();

			sys.PostUpdate();
			
			delta = 1 / clock.restart().asSeconds();
		}
		std::cout << std::endl;
		window.setActive(false);
	});

	auto physic = std::thread([&window, &sys, &delta] {
		sf::Clock deltaClock;
		const sf::Time fixedDelta = sf::seconds(1.0f / 60);
		sf::Time sinceUpdate = sf::Time::Zero;

		while (window.isOpen()) {
			sinceUpdate += deltaClock.restart();

			if (sinceUpdate > fixedDelta) {
				sinceUpdate -= fixedDelta;
				sys.FixedUpdate();
				std::cout << "FPS: " << delta << "\r";
			}
		}
	});
	
	sys.PostInit();
	render.join();
	window.setActive(true);
	physic.join();
}
