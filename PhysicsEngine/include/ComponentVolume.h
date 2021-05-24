#pragma once

#include "Component.h"
#include "Entity.h"
#include <queue>
#include "SFML/System/Vector2.hpp"

struct ComponentVolume : public ComponentData<ComponentVolume>
{
	std::queue<Entity*> Perimetr_drops;
	sf::Vector2f Top_Position;
	sf::Vector2f Bottom_Position_Interract_Wall;
	bool Is_Interract_Wall = false;
};