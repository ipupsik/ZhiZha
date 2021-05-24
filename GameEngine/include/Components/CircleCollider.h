#include "Component.h"
#include "Entity.h"
#include "SFML/System/Vector2.hpp"

struct CircleCollider : public ComponentData<CircleCollider>
{
	float Radius;
};
