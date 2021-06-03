#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include "Component.h"

struct SpriteComponent : public ComponentData<SpriteComponent> {
	sf::Sprite* Sprite;
};