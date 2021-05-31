#pragma once

#include "System.h"
#include "SFML/Graphics.hpp"

class CameraMovingSystem : public virtual FixedUpdateSystem {
	sf::Vector2f& _camera_location;

public:
	explicit CameraMovingSystem(sf::Vector2f& camera_location)
		: _camera_location(camera_location){ }

	void OnFixedUpdate() override;
};