#include "Component.h"
#include "Entity.h"
#include "SFML/System/Vector2.hpp"
#include <vector>

struct ComponentDrop : public ComponentData<ComponentDrop>
{
	std::vector<Entity*> neighbours;
	sf::Vector2f Neighbour_impact;
	sf::Vector2f Forse;
	bool is_moved, is_in_volume, is_in_queue, is_force_calculated;
};