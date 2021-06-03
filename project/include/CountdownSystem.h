#pragma once

#include "ResourceManager.h"
#include "GameTime.h"
#include "System.h"

class CountdownSystem : public virtual InitSystem,
						public virtual UpdateSystem,
						public virtual UnloadSystem {
	Entity* _textEntity;
	sf::Text _text;
	ResourceManager& _resources;
	GameTime& _time;

	static constexpr auto _timeToPlay = 40.;

public:
	CountdownSystem(ResourceManager& resources, GameTime& time)
		: _resources(resources), _time(time) {}

	void OnUpdate() override;
	void OnInit() override;
	void OnSceneUnload(Scene scene) override;
};