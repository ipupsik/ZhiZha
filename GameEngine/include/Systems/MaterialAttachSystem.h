#pragma once

#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

class MaterialAttachSystem : public virtual InitSystem {
	sf::Window& _window;

public:
	explicit MaterialAttachSystem(sf::Window& window) : _window(window) {}

	void OnInit() override;
};
