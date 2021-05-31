#pragma once
#include "GameTime.h"
#include "ResourceManager.h"
#include "System.h"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/Graphics.hpp"

class RotateSystem : public virtual FixedUpdateSystem {
	sf::View& _gameView;
	double _dphi = 0;
	double _ddphi = 0;
	float& _phi;
	sf::Vector2f& _gravitation;
	GameTime& _time;
	sf::RectangleShape* _line;

public:
	RotateSystem(sf::View& gameView, sf::Vector2f& gravitation, GameTime& time, float& phi)
		: _gameView(gameView),
		  _gravitation(gravitation),
		  _time(time), _phi(phi) {}

	void OnFixedUpdate() override;
};
