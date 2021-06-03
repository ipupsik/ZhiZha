#pragma once

#include <SFML/Graphics/View.hpp>
#include <ResourceManager.h>
#include <Engine.h>
#include "System.h"

class MenuSystem : public virtual InitSystem,
				   public virtual UnloadSystem,
				   public virtual UpdateSystem {
	Engine& _engine;
	ResourceManager& _resources = _engine.GetResourceManager();
	std::vector<Entity*> _createdEntities;
	sf::RenderWindow& _window;
	sf::Text _startText, _endText, _namingText;

public:
	explicit MenuSystem(Engine& engine, sf::RenderWindow& window)
			:_engine(engine), _window(window) { }

	void OnInit() override;
	void OnSceneUnload(Scene scene) override;
	void OnUpdate() override;
};