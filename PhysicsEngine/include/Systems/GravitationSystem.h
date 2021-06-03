#pragma once

#include "System.h"
#include "GameTime.h"

class GravitationSystem : public virtual FixedUpdateSystem, public virtual UnloadSystem {
	GameTime& _gameTime;
	sf::Vector2f& _gravitation;

public:
	explicit GravitationSystem(GameTime& gameTime, sf::Vector2f& gravitation)
		: _gameTime(gameTime)
		, _gravitation(gravitation) {}

	void OnFixedUpdate() override;
	void OnSceneUnload(Scene scene) override;
};