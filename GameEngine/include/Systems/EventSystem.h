#pragma once

#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

/**
 * Эта система используется для обработки связанной с окном: передвинули мышку, растянули окно или
 * нажали кнопку.
 */
class EventSystem : public virtual PostInitSystem {
	sf::RenderWindow& _window;

public:
	explicit EventSystem(sf::RenderWindow& window): _window(window) {}

	void OnPostInit() override;
};
