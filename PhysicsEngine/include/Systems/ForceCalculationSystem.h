#pragma once

#include "System.h"
#include "GameTime.h"

class ForceCalculationSystem : public virtual FixedUpdateSystem {
	GameTime& _gameTime;
	sf::Vector2f& _gravitation;

public:
	void FindVolumPositions(Entity& drop, sf::Vector2f& Top_Position, sf::Vector2f& Bottom_Position_Interract_Wall);
	void ForceCalculation(Entity& drop, sf::Vector2f& Top_Position, sf::Vector2f& Bottom_Position_Interract_Wall);
	explicit ForceCalculationSystem(GameTime& gameTime, sf::Vector2f& gravitation)
		: _gameTime(gameTime)
		, _gravitation(gravitation) {}

	void OnFixedUpdate() override;
};
