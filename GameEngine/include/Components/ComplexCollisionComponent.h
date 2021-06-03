#include "Component.h"
#include "Entity.h"
#include "SFML/System/Vector2.hpp"
#include <vector>

struct ComplexCollisionComponent : public ComponentData<ComplexCollisionComponent>
{
	struct Triangle{
		sf::Vector2f v1, v2, v3;
	};

	std::vector<Triangle> ComplexCollision;
};
