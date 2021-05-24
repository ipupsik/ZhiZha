#pragma once

#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

/**
 * Эта система используется для обработки связанной с окном: передвинули мышку, растянули окно или
 * нажали кнопку.
 */
class EventSystem : public virtual PostInitSystem {
	sf::RenderWindow& _window;
	sf::View _gameView;

public:
	explicit EventSystem(sf::RenderWindow& window, sf::View gameView)
		: _window(window), _gameView(gameView) {}

	void OnPostInit() override;
};
