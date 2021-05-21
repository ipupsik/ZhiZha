#pragma once

#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

class ActorRenderSystem : public virtual PostUpdateSystem {
	sf::Window& _window;

public:
	explicit ActorRenderSystem(sf::Window& window): _window(window) {}

	void OnPostUpdate() override;
};