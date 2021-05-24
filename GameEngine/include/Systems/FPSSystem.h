#pragma once
#include "System.h"
#include "SFML/Graphics.hpp"
#include "../GameTime.h"
#include "ResourceManager.h"

class FPSSystem : public virtual FixedUpdateSystem, public virtual InitSystem {
	GameTime& _time;
	sf::Text _fps;
	sf::Font _font;
	ResourceManager& _resources;

public:
	explicit FPSSystem(GameTime& time, ResourceManager& resources)
		: _time(time), _resources(resources) { }

	void OnFixedUpdate() override;
	void OnInit() override;
};
