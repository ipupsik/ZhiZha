#pragma once
#include "System.h"
#include "../GameTime.h"

class FPSSystem: public virtual PostUpdateSystem {
	GameTime& _time;
	
public:
	explicit FPSSystem(GameTime& time)
		: _time(time) {}

	void OnPostUpdate() override;
};