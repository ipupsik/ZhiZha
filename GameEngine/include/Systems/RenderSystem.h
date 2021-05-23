#pragma once

#include "System.h"
#include "SFML/Graphics.hpp"

class RenderSystem: public virtual PostUpdateSystem {
	sf::RenderWindow& _window;

public:
	explicit RenderSystem(sf::RenderWindow& window)
			:_window(window) { }

	void OnPostUpdate() override;
};