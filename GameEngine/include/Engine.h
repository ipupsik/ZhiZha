#pragma once
#include "EntityManager.h"
#include "SystemManager.h"
#include "ResourceManager.h"
#include "GameTime.h"
#include "SFML/Graphics/RenderWindow.hpp"

class SystemRegisteringHelper;

class Engine {
	EntityManager* _entityManager = new EntityManager();
	SystemManager* _systemManager = new SystemManager(*_entityManager);
	ResourceManager* _resourceManager = new ResourceManager();
	GameTime* _time = new GameTime();
	sf::RenderWindow& _window;
	Scene _currentScene;
	bool _isActive = false;

	void initRenderThread();
	void initFixedUpdateThread() const;

public:
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	~Engine();

	explicit Engine(sf::RenderWindow& window)
			:_window(window) { }

	[[nodiscard]] EntityManager& GetEntityManager() const { return *_entityManager; }
	[[nodiscard]] SystemManager& GetSystemManager() const { return *_systemManager; }
	[[nodiscard]] ResourceManager& GetResourceManager() const { return *_resourceManager; }
	[[nodiscard]] GameTime& GetTime() const { return *_time; }

	template <typename T, typename Stub = SystemRegisteringHelper, typename ...Args>
	// compiler cannot compile cyclic classes, but can lazily compile it with templates
	requires std::derived_from<T, System>
	Stub RegisterSystem(Args&& ... args) {
		T* instance = new T(std::forward<Args>(args)...);
		_systemManager->RegisterSystem<T>(instance);
		return Stub(*this, instance);
	}

	void LoadScene(Scene scene);
	void UnloadScene();
	void Start();
	void Stop();

	bool IsActive() { return _isActive; }
};

class SystemRegisteringHelper {
	Engine& _engine;
	System* _system;

public:
	SystemRegisteringHelper(Engine& engine, System* system)
			:_engine(engine), _system(system) { }

	template <typename T, typename ...Args>
	SystemRegisteringHelper RegisterSystem(Args&& ... args) {
		return _engine.RegisterSystem<T>(std::forward<Args>(args)...);
	}

	SystemRegisteringHelper& BindToScene(Scene scene) {
		_system->BindToScene(scene);
		return *this;
	}

	SystemRegisteringHelper& UnbindFromScene(Scene scene) {
		_system->UnbindFromScene(scene);
		return *this;
	}

	Engine& BindStatic() {
		BindToScene(Scene::Menu).BindToScene(Scene::Main).BindToScene(Scene::End);
		return _engine;
	}
};