#include "Component.h"
#include "Entity.h"
#include "SFML/System/Vector2.hpp"

struct BoxCollider : public ComponentData<BoxCollider>
{
	sf::Vector2f Scale;
};
