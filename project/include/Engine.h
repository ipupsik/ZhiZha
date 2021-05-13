#pragma once
#include "EntityManager.h"
#include "SystemManager.h"
#include "Systems.h"
#include "SFML/Window/Window.hpp"

class Engine {
	EntityManager& _entityManager = EntityManager::Current;
	SystemManager& _systemManager = SystemManager::Current;
	sf::Window& _window;
	float _deltaTime = 0;

	void initRenderThread();
	void initFixedUpdateThread() const;

public:
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	explicit Engine(sf::Window&& window): _window(window) {
		RegisterSystem<EventSystem>(EventSystem(window));
	}

	[[nodiscard]] EntityManager& EntityManager() const { return _entityManager; }

	template <typename T, typename ...Args>
		requires std::derived_from<T, System<T>>
	Engine& RegisterSystem(Args&&... args) {
		_systemManager.RegisterSystem<T>(std::forward<Args>(args)...);
		return *this;
	}

	void Start();
};
