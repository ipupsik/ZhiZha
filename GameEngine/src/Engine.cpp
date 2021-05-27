#include <thread>

#include "Engine.h"
#include "glad/glad.h"

void Engine::initRenderThread() {
	_window.setActive(true);

	glOrtho(-1.4, 1.4, -1.4, 1.4, -1, 8);
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	while (_window.isOpen()) {
		_window.clear(sf::Color { 100, 100, 255, 255 });
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
	_systemManager->Init();
	_window.setActive(false);
	std::thread update([&] { initRenderThread(); });
	std::thread fixed([&] { initFixedUpdateThread(); });

	_systemManager->PostInit();
	update.join();
	_window.setActive(true);
	fixed.join();
}
