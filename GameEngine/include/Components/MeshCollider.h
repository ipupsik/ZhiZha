#pragma once

#include "Component.h"
#include "Entity.h"
#include "SFML/System/Vector2.hpp"

struct MeshCollider : public ComponentData<MeshCollider>
{
	struct face
	{
		sf::Vector2f v1, v2, v3;
	};
	std::vector<face> Collision;
};