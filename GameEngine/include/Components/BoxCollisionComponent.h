#include "Component.h"
#include "Entity.h"
#include "Components.h"
#include "SFML/System/Vector2.hpp"

struct BoxCollisionComponent : public ComponentData<BoxCollisionComponent>
{
	sf::Vector2f Position, Scale;
};
