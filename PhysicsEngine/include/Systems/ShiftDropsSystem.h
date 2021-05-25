#pragma once

#include "System.h"
#include "GameTime.h"

class ShiftDropsSystem : public virtual FixedUpdateSystem {
	GameTime& _gameTime;

public:
	explicit ShiftDropsSystem(GameTime& gameTime)
		: _gameTime(gameTime) {}

	void OnFixedUpdate() override;
};