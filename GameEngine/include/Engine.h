#pragma once
#include "EntityManager.h"
#include "SystemManager.h"
#include "ResourceManager.h"
#include "Systems.h"
#include "SFML/Window/Window.hpp"

class Engine {
	EntityManager& _entityManager = EntityManager::Current;
	SystemManager& _systemManager = SystemManager::Current;
	ResourceManager* _resourceManager = new ResourceManager();
	sf::Window& _window;
	float _deltaTime;

	void initRenderThread();
	void initFixedUpdateThread();

public:
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	~Engine() { delete _resourceManager; }

	explicit Engine(sf::Window& window): _window(window) {}

	[[nodiscard]] EntityManager& GetEntityManager() const { return _entityManager; }
	[[nodiscard]] ResourceManager& GetResourceManager() const { return *_resourceManager; }

	template <typename T, typename ...Args>
		requires std::derived_from<T, System>
	Engine& RegisterSystem(Args&&... args) {
		_systemManager.RegisterSystem<T>(std::forward<Args>(args)...);
		return *this;
	}

	void Start();
};
