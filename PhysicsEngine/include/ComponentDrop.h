#include "Component.h"
#include "Entity.h"
#include "SFML/System/Vector2.hpp"

struct ComponentDrop : public ComponentData<ComponentDrop>
{
	std::vector<Entity*> neighbours;
	sf::Vector2f Neighbour_impact;
	bool is_moved, is_in_valume, is_in_queue;
};