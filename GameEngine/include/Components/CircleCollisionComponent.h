#include "Component.h"
#include "Entity.h"
#include "SFML/System/Vector2.hpp"

struct CircleCollisionComponent : public ComponentData<CircleCollisionComponent>
{
	sf::Vector2f Position;
	float Radius;
};
