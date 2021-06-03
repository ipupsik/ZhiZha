#pragma once

#include "ResourceManager.h"
#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

class Stone_1_InitSystem : public virtual InitSystem, public virtual UnloadSystem {
	ResourceManager& _resources;
	Entity* _stone;

public:
	explicit Stone_1_InitSystem(ResourceManager& resources);

	void OnInit() override;
	void OnSceneUnload(Scene scene) override;
};