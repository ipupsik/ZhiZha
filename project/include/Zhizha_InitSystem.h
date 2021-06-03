#pragma once

#include "ResourceManager.h"
#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

class Zhizha_InitSystem : public virtual InitSystem, public virtual UnloadSystem {
	ResourceManager& _resources;
	std::vector<Entity*> _createdEntities;

public:
	explicit Zhizha_InitSystem(ResourceManager& resources);

	void OnInit() override;
	void OnSceneUnload(Scene scene) override;
};