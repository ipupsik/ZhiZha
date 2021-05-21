#pragma once

#include "Component.h"
#include "SFML/System/Vector2.hpp"

struct TransformComponent : public ComponentData<TransformComponent> {
	sf::Vector2f Location, Rotation, Scale;
};
