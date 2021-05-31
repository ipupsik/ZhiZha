#pragma once

#include "ResourceManager.h"
#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

class SmallBrunch_InitSystem : public virtual InitSystem {
	ResourceManager& _resources;

public:
	explicit SmallBrunch_InitSystem(ResourceManager& resources);

	void OnInit() override;
};