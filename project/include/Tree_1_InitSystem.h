#pragma once

#include "ResourceManager.h"
#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

class Tree_1_InitSystem : public virtual InitSystem {
	ResourceManager& _resources;

public:
	explicit Tree_1_InitSystem(ResourceManager& resources);

	void OnInit() override;
};