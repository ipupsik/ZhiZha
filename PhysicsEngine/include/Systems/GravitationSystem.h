#pragma once

#include "System.h"
#include "GameTime.h"

class GravitationSystem : public virtual FixedUpdateSystem {
	GameTime& _gameTime;
	sf::Vector2f& _gravitation;

public:
	explicit GravitationSystem(GameTime& gameTime) : _gameTime(gameTime) {}

	void OnFixedUpdate() override;
};