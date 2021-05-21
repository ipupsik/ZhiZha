#pragma once
#include "System.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "../GameTime.h"
#include "ResourceFile.h"

class FPSSystem: public virtual PostUpdateSystem, public virtual FixedUpdateSystem {
	GameTime& _time;
	sf::Text _fps;
	sf::Font _font;
	sf::RenderWindow& _window;

public:
	explicit FPSSystem(GameTime& time, sf::RenderWindow& window)
		: _time(time), _window(window) {
		_font.loadFromFile(ResourceFile("JetBrainsMono-Regular.ttf").Name());
		_fps.setFont(_font);
		_fps.setCharacterSize(24);
	}

	void OnPostUpdate() override;
	void OnFixedUpdate() override;
};