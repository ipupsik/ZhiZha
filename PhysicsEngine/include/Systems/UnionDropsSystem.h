#pragma once

#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"


class UnionDropsSystem : public virtual FixedUpdateSystem {
	sf::Window& _window;
	void CheckAndAddDrop(ComponentVolume& volume_component, ComponentDrop& component_drop, Entity& drop);
	void AddToVolume(auto& volume_component, Entity& drop);

public:
	explicit UnionDropsSystem(sf::Window& window) : _window(window) {}

	void OnFixedUpdate() override;
};