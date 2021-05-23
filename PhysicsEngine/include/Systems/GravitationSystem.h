#pragma once

#include "System.h"
#include "GameTime.h"

class GravitationSystem : public virtual FixedUpdateSystem {
	GameTime& _gameTime;

public:
	explicit GravitationSystem(GameTime& gameTime) : _gameTime(gameTime) {}

	void OnFixedUpdate() override;
};