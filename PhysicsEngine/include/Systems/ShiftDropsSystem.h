#pragma once

#include "System.h"
#include "GameTime.h"

class ShiftDropsSystem : public virtual FixedUpdateSystem {
	GameTime& _gameTime;

public:
	explicit ShiftDropsSystem(GameTime& gameTime)
		: _gameTime(gameTime) {}

	void MomentumConservation(SpeedComponent& currentSpeed, SpeedComponent& neighborSpeed, ComponentDrop& neighborDrop);
	void ÑhangeSpeed(SpeedComponent& currentSpeed, ComponentDrop& currentDrop, sf::Vector2f& newSpeed);

	void OnFixedUpdate() override;
};