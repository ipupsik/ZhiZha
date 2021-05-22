#pragma once

#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

class UnionDropsSystem : public virtual FixedUpdateSystem {
	sf::Window& _window;

public:
	explicit UnionDropsSystem(sf::Window& window) : _window(window) {}

	void OnFixedUpdate() override;
};