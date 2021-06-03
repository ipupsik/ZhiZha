#pragma once

#include "ResourceManager.h"
#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

class SmallBrunch_InitSystem : public virtual InitSystem, public virtual UnloadSystem {
	ResourceManager& _resources;
	Entity* _brunch;

public:
	explicit SmallBrunch_InitSystem(ResourceManager& resources);

	void OnInit() override;
	void OnSceneUnload(Scene scene) override;
};