#pragma once

#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

class ComplexCollisionSystem : public virtual FixedUpdateSystem {
public:

	void OnFixedUpdate() override;
};