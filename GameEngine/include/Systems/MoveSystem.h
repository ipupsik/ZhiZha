#pragma once

#include "System.h"
#include "Components/TransformComponent.h"
#include "GameTime.h"
#include <random>
#include <ctime>
#include "Components/SpeedComponent.h"

class MoveSystem : public virtual UpdateSystem {
	GameTime& _time;
	std::default_random_engine random = std::default_random_engine(time(nullptr));

public:
	explicit MoveSystem(GameTime& time)
			: _time(time) { }

	void OnUpdate() override {
		const auto& items = _entities->GetEntitiesBy<TransformComponent, SpeedComponent>();

		for (auto& [components, entity] : items) {
			auto& [transform, dt] = components;
			transform->Location.x += (dt->Speed * _time.FixedDeltaTime());
		}
	}
};