#pragma once

#include "System.h"

class ResetParamsSystem : public virtual FixedUpdateSystem {
public:
	void OnFixedUpdate() override;
};