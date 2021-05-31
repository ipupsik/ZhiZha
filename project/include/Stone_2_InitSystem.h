#pragma once

#include "ResourceManager.h"
#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

class Stone_2_InitSystem : public virtual InitSystem {
	ResourceManager& _resources;

public:
	explicit Stone_2_InitSystem(ResourceManager& resources);

	void OnInit() override;
};