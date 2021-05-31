#pragma once

#include "Component.h"
#include "Components/MaterialComponent.h"
#include "glad/glad.h"

struct ZhizhaVolumeComponent : public ComponentData<ZhizhaVolumeComponent>
{
	MaterialComponent* material;
	GLuint indexVBO, indexVAO, indexEBO;

	std::vector<sf::Vector2f> vertices[2];
	int side = 0;
};
