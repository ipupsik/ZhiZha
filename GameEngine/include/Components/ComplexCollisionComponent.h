#pragma once

#include "Component.h"
#include "Entity.h"
#include "SFML/System/Vector2.hpp"

struct ComplexCollisionComponent : public ComponentData<ComplexCollisionComponent>
{
	struct face
	{
		sf::Vector2f v1, v2, v3;
	};
	std::vector<face> Collision;
};