#pragma once

#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

class CollisionSystem : public virtual FixedUpdateSystem {
public:
	void OnFixedUpdate() override;
};