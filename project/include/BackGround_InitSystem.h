#pragma once

#include "ResourceManager.h"
#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

class BackGround_InitSystem : public virtual InitSystem {
	ResourceManager& _resources;

public:
	explicit BackGround_InitSystem(ResourceManager& resources);

	void OnInit() override;
};