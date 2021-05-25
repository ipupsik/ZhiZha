#pragma once

#include "Component.h"
#include "MeshResource.h"
#include "SFML/Graphics/Drawable.hpp"

struct RenderedComponent : public ComponentData<RenderedComponent>
{
	sf::Drawable* DrawableObj;
};