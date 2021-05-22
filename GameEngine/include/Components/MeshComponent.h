#pragma once

#include "Component.h"
#include "MeshResource.h"
#include "SFML/Graphics/Drawable.hpp"

struct MeshComponent : public ComponentData<MeshComponent>
{
	sf::Drawable* Drawable;
};
