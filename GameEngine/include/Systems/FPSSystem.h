#pragma once
#include "System.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "../GameTime.h"
#include "ResourceFile.h"
#include "ResourceManager.h"

class FPSSystem: public virtual PostUpdateSystem, public virtual FixedUpdateSystem {
	GameTime& _time;
	sf::Text _fps;
	sf::Font _font;
	sf::RenderWindow& _window;
	ResourceManager& _resources;

public:
	explicit FPSSystem(GameTime& time, sf::RenderWindow& window, ResourceManager& resources)
		: _time(time), _window(window), _resources(resources) {
		auto font = _resources.GetOrAddResource<ResourceFile>("JetBrainsMono-Regular.ttf");
		_font.loadFromStream(*font);
		_fps.setFont(_font);
		_fps.setCharacterSize(24);
	}

	void OnPostUpdate() override;
	void OnFixedUpdate() override;
};