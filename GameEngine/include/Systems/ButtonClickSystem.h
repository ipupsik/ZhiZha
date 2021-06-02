#pragma once

#include "System.h"

class ButtonClickSystem : public virtual UpdateSystem {
	sf::Window& _window;

public:
	explicit ButtonClickSystem(sf::Window& window);

	void OnUpdate() override;
};