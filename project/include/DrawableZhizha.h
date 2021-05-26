#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/System/Vector3.hpp"

#include "Components/MaterialComponent.h"
#include "Components/TransformComponent.h"
#include "Components/MeshComponent.h"

#include <vector>

#include <utility>

class DrawableZhizha : public sf::Drawable {
public:
	MaterialComponent *material;
	std::vector<float> vertices;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};