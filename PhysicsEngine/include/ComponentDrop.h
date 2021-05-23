#include "Component.h"
#include "Entity.h"
#include "SFML/System/Vector2.hpp"

struct ComponentDrop : public ComponentData<ComponentDrop>
{
	std::vector<Entity*> neighbours;
	sf::Vector2f Neighbour_impact;
	sf::Vector2f Forse;
	sf::Vector2f Velocity;
	sf::Vector2f Position;
	bool is_moved, is_in_volume, is_in_queue, is_force_calculated;
};