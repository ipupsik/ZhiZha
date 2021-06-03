#include <Engine.h>
#include "System.h"
#include "SFML/Graphics.hpp"
#include "GameTime.h"

class EndSystem : public virtual FixedUpdateSystem {
	Engine& _engine;

public:
	explicit EndSystem(Engine& engine)
		: _engine(engine) {}

	void OnFixedUpdate() override;
};
		