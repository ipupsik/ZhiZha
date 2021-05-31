#pragma once

#include "ResourceManager.h"
#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

class SmallSkull_InitSystem : public virtual InitSystem {
	ResourceManager& _resources;

public:
	explicit SmallSkull_InitSystem(ResourceManager& resources);

	void OnInit() override;
};