#pragma once
#include "GameTime.h"
#include "ResourceManager.h"
#include "System.h"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/Graphics.hpp"

class RotateSystem : public virtual UpdateSystem, public virtual InitSystem {
	sf::View& _gameView;
	double _dphi = 0;
	double _ddphi = 0;
	double _phi = 0;
	sf::Vector2f& _gravitation;
	GameTime& _time;
	sf::RectangleShape* _line;

public:
	RotateSystem(sf::View& gameView, sf::Vector2f& gravitation, GameTime& time)
		: _gameView(gameView),
		  _gravitation(gravitation),
		  _time(time) {}

	void OnUpdate() override;
	void OnInit() override;
};
