#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/System/Vector3.hpp"

#include "Components/MaterialComponent.h"
#include "Components/TransformComponent.h"
#include "Components/MeshComponent.h"
#include "MeshResource.h"

#include <vector>

#include <utility>

class DrawableZhizha : public sf::Drawable {
public:
	MaterialComponent *material;
	GLuint indexVBO, indexVAO, indexEBO;
	std::vector<sf::Vector2f> vertices[2];
	int side = 0;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void initMesh();
};