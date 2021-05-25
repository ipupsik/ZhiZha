#pragma once

#include "System.h"
#include "SFML/Graphics.hpp"

class RenderSystem: public virtual PostUpdateSystem {
	sf::RenderWindow& _window;
	std::vector<sf::View>& _views;

public:
	explicit RenderSystem(sf::RenderWindow& window, std::vector<sf::View>& views)
		: _window(window), _views(views) { }

	void OnPostUpdate() override;
};