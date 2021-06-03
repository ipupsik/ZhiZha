#pragma once

#include "Component.h"
#include "ComponentVolume.h"
#include "Entity.h"
#include "SFML/System/Vector2.hpp"
#include <vector>

struct ComponentDrop : public ComponentData<ComponentDrop>
{
	std::vector<Entity*> neighbours;
	ComponentVolume Volum_Component;
	sf::Vector2f Neighbour_impact;
	sf::Vector2f Forse;
	sf::Vector2f OldLocation = { 0,0 };
	size_t OldLocationCounter = 0;
	bool is_moved, is_in_volume, is_in_queue, is_force_calculated, is_volume_calculated, if_changed_speed;
};