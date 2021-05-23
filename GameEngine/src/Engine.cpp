#include <thread>

#include "Engine.h"
#include "glad/glad.h"

void Engine::initRenderThread() {
	_window.setActive(true);

	glOrtho(-1.4, 1.4, -1.4, 1.4, 0, 8);
	glEnable(GL_DEPTH_TEST);
	while (_window.isOpen()) {
		_systemManager->Update();

		glClearColor(0.4f, 0.4f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
