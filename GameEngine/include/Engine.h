#pragma once
#include "EntityManager.h"
#include "SystemManager.h"
#include "ResourceManager.h"
#include "Systems.h"
#include "SFML/Window/Window.hpp"

class Engine {
	EntityManager* _entityManager = new EntityManager();
	SystemManager* _systemManager = new SystemManager(*_entityManager);
	ResourceManager* _resourceManager = new ResourceManager();
	sf::Window& _window;
	float _deltaTime = 0.0f;

	void initRenderThread();
	void initFixedUpdateThread() const;

public:
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	~Engine();

	explicit Engine(sf::RenderWindow& window): _window(window) {}

	[[nodiscard]] EntityManager& GetEntityManager() const { return *_entityManager; }
	[[nodiscard]] SystemManager& GetSystemManager() const { return *_systemManager; }
	[[nodiscard]] ResourceManager& GetResourceManager() const { return *_resourceManager; }

	template <typename T, typename ...Args>
		requires std::derived_from<T, System>
	Engine& RegisterSystem(Args&&... args) {
		T* instance = new T(std::forward<Args>(args)...);
		_systemManager->RegisterSystem<T>(instance);
		return *this;
	}

	void Start();
};
