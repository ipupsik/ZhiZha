#pragma once

#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

class SlipSystem : public virtual FixedUpdateSystem {
public:
	void OnFixedUpdate() override;
};