#pragma once

#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Engine.h"

/**
 * Эта система используется для обработки связанной с окном: передвинули мышку, растянули окно или
 * нажали кнопку.
 */
class EventSystem : public virtual PostInitSystem {
	sf::RenderWindow& _window;
	sf::View _gameView;
	Engine& _engine;

public:
	explicit EventSystem(sf::RenderWindow& window, sf::View gameView, Engine& engine)
		: _window(window), _gameView(gameView), _engine(engine) {}

	void OnPostInit() override;
};
