#pragma once

#include <SFML/Graphics/View.hpp>
#include <ResourceManager.h>
#include <Engine.h>
#include "System.h"

class MenuSystem : public virtual InitSystem, public virtual UpdateSystem, public virtual UnloadSystem {
	Engine& _engine;
	ResourceManager& _resources = _engine.GetResourceManager();
	std::vector<Entity*> _createdEntities;
	sf::Window& _window;

public:
	explicit MenuSystem(Engine& engine, sf::Window& window)
		: _engine(engine), _window(window) {}

	void OnInit() override;
	void OnUpdate() override;
	void OnSceneUnload(Scene scene) override;
};