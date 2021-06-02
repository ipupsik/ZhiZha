#pragma once

#include <SFML/Graphics/View.hpp>
#include <ResourceManager.h>
#include <Engine.h>
#include "System.h"

class MenuSystem : public virtual InitSystem, public virtual UpdateSystem, public virtual UnloadSystem {
	sf::View& _menuView;
	Engine& _engine;
	ResourceManager& _resources = _engine.GetResourceManager();
	std::vector<Entity*> _createdEntities;
	sf::Window& _window;

public:
	explicit MenuSystem(sf::View& menuView, Engine& engine, sf::Window& window)
		: _menuView(menuView), _engine(engine), _window(window) {}

	void OnInit() override;
	void OnUpdate() override;
	void OnSceneUnload(Scene scene) override;
};