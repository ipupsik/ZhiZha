#pragma once
#include "System.h"
#include "SFML/Graphics.hpp"
#include "../GameTime.h"
#include "ResourceManager.h"

class FPSSystem : public virtual FixedUpdateSystem,
				  public virtual InitSystem,
				  public virtual UpdateSystem,
				  public virtual UnloadSystem {
	GameTime& _time;
	sf::Text _fps;
	ResourceManager& _resources;
	Entity* _fontEntity;
	bool _wasF3Pressed = false;

public:
	explicit FPSSystem(GameTime& time, ResourceManager& resources)
			:_time(time), _resources(resources) { }

	void OnFixedUpdate() override;
	void OnInit() override;
	void OnUpdate() override;
	void OnSceneUnload(Scene scene) override;
};
