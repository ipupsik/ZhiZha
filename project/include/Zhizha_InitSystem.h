#pragma once

#include "ResourceManager.h"
#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

class Zhizha_InitSystem : public virtual InitSystem {
	ResourceManager& _resources;

public:
	explicit Zhizha_InitSystem(ResourceManager& resources);

	void OnInit() override;
};