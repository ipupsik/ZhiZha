#pragma once

#include "System.h"

class ShiftDropsSystem : public virtual FixedUpdateSystem {
public:
	void OnFixedUpdate() override;
}