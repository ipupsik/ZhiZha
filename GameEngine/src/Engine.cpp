#include <thread>
#include <iostream>
#include <algorithm>

#include "Engine.h"

void Engine::initRenderThread() {
	sf::Clock clock{};
	_window.setActive(true);

	while (_window.isOpen()) {
		_systemManager.Update();
		_systemManager.PostUpdate();
		_deltaTime = clock.restart().asSeconds();
	}

	_window.setActive(false);
}

void Engine::initFixedUpdateThread() {
	const sf::Time fixedTime = sf::seconds(1 / 30.0f);
	sf::Clock deltaClock{};
	sf::Time sinceUpdate = sf::Time::Zero;

	while (_window.isOpen()) {
		sinceUpdate += deltaClock.restart();

		if (sinceUpdate > fixedTime) {
			sinceUpdate -= fixedTime;
			std::cout << "FPS: " << 1 / _deltaTime << '\r';
			_systemManager.FixedUpdate();
		}
	}
}

void Engine::Start() {
	_systemManager.Init();
	_window.setActive(false);
	std::thread update([&] { initRenderThread(); });
	std::thread fixed([&] { initFixedUpdateThread(); });

	_systemManager.PostInit();
	update.join();
	_window.setActive(true);
	fixed.join();
}
