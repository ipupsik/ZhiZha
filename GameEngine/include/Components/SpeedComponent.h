#pragma once

#include "Component.h"

struct SpeedComponent : public ComponentData<SpeedComponent> {
	sf::Vector2f Speed;
};