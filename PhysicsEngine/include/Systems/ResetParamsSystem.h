#pragma once

#include "System.h"

class ResetParamsSystem : public virtual FixedUpdateSystem {
	sf::Vector2f& _camera_location;
public:
	explicit ResetParamsSystem(sf::Vector2f& camera_location) : _camera_location(camera_location)
	{}

	void OnFixedUpdate() override;
};