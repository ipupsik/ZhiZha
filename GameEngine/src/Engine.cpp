#include <thread>
#include <iostream>
#include <iomanip>

#include "Engine.h"
#include <glad/glad.h>
#include "SFML/OpenGL.hpp"

void Engine::initRenderThread() {
	sf::Clock clock{};
	_window.setActive(true);

	glOrtho(-1.4, 1.4, -1.4, 1.4, 0, 8);
	glEnable(GL_DEPTH_TEST);
	while (_window.isOpen()) {
		_systemManager->Update();

		glClearColor(0.4f, 0.4f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_systemManager->PostUpdate();
		_window.display();

		_deltaTime = clock.restart().asSeconds();
	}

	_window.setActive(false);
}

void Engine::initFixedUpdateThread() const {
	const sf::Time fixedTime = sf::seconds(1 / 24.0f);
	sf::Clock deltaClock{};
	sf::Time sinceUpdate = sf::Time::Zero;

	while (_window.isOpen()) {
		sinceUpdate += deltaClock.restart();

		if (sinceUpdate > fixedTime) {
			sinceUpdate -= fixedTime;
			std::cout << "FPS: " << static_cast<long long>(1 / _deltaTime) << '\r';
			_systemManager->FixedUpdate();
		}
	}
}

Engine::~Engine() {
	delete _systemManager;
	delete _resourceManager;
	delete _entityManager;
}

void Engine::Start() {
	_systemManager->Init();
	_window.setActive(false);
	std::thread update([&] { initRenderThread(); });
	std::thread fixed([&] { initFixedUpdateThread(); });

	_systemManager->PostInit();
	update.join();
	_window.setActive(true);
	fixed.join();
}
