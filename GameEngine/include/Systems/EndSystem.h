#include "System.h"
#include "SFML/Graphics.hpp"
#include "GameTime.h"

class EndSystem : public virtual FixedUpdateSystem {
	GameTime& _time;

public:
	explicit EndSystem(GameTime& time)
		: _time(time) {}

	void OnFixedUpdate() override;
};
		