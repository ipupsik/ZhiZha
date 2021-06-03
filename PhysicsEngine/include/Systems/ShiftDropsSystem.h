#pragma once

#include "System.h"
#include "GameTime.h"

#include "ComponentDrop.h"
#include "ComponentVolume.h"
#include "Components/SpeedComponent.h"

class ShiftDropsSystem : public virtual FixedUpdateSystem {
	GameTime& _gameTime;
	sf::Vector2f& _gravitation;
	sf::Vector2f& _camera_location;

public:
	explicit ShiftDropsSystem(GameTime& gameTime, sf::Vector2f& gravitation, sf::Vector2f& camera_location)
		: _gameTime(gameTime)
		, _gravitation(gravitation)
		, _camera_location(camera_location) {}

	void MomentumConservation(SpeedComponent& currentSpeed, SpeedComponent& neighborSpeed, ComponentDrop& neighborDrop);
	void ChangeSpeed(SpeedComponent& currentSpeed, ComponentDrop& currentDrop, sf::Vector2f& newSpeed);

	void OnFixedUpdate() override;
};