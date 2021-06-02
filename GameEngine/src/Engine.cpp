#include <thread>
#include <iostream>

#include "Engine.h"
#include "glad/glad.h"

void Engine::initRenderThread() {
	_window.setActive(true);

	glOrtho(-1.4, 1.4, -1.4, 1.4, -1, 8);
	while (_window.isOpen()) {
		_window.clear(sf::Color { 0, 0, 0, 255 });
		_systemManager->Update();
		_systemManager->PostUpdate();
		_window.display();

		_time->waitForUpdate();
	}

	_window.setActive(false);
}

void Engine::initFixedUpdateThread() const {
	while (_window.isOpen()) {
		_systemManager->FixedUpdate();

		_time->waitForFixedUpdate();
	}
}

Engine::~Engine() {
	delete _systemManager;
	delete _resourceManager;
	delete _entityManager;
}

void Engine::Start() {
	std::thread update([&] { initRenderThread(); });
	std::thread fixed([&] { initFixedUpdateThread(); });

	_systemManager->PostInit();
	update.join();
	_window.setActive(true);
	fixed.join();
}

void Engine::LoadScene(Scene scene) {
	std::cout << "Loading scene #" << static_cast<int>(scene) << "..." << std::endl;
	_systemManager->ActivateInitSystems(scene);
	_window.setActive(true);
	_systemManager->Init();
	_window.setActive(false);

	_systemManager->ActivateUpdateSystems(scene);
}
