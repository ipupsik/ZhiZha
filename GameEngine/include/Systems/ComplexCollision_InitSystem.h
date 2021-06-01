#pragma once

#include "System.h"
#include "SFML/Graphics.hpp"

class ComplexCollision_InitSystem : public virtual InitSystem {
public:
	explicit ComplexCollision_InitSystem(){ }

	void OnInit() override;
}; 