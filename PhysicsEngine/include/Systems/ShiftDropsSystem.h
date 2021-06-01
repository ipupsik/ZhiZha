#pragma once

#include "System.h"
#include "GameTime.h"

#include "ComponentDrop.h"
#include "ComponentVolume.h"
#include "Components/SpeedComponent.h"

class ShiftDropsSystem : public virtual FixedUpdateSystem {
	GameTime& _gameTime;
	sf::Vector2f& _gravitation;

public:
	explicit ShiftDropsSystem(GameTime& gameTime, sf::Vector2f& gravitation)
		: _gameTime(gameTime)
		, _gravitation(gravitation) {}

	void MomentumConservation(SpeedComponent& currentSpeed, SpeedComponent& neighborSpeed, ComponentDrop& neighborDrop);
	void ÑhangeSpeed(SpeedComponent& currentSpeed, ComponentDrop& currentDrop, sf::Vector2f& newSpeed);

	void OnFixedUpdate() override;
};