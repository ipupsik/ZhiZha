#pragma once

#include "Component.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/System/Vector3.hpp"

struct TransformComponent : public ComponentData<TransformComponent> {
	sf::Vector2f Location, Scale;
	float Angle;
	TransformComponent* parent;
};

struct MyTransformComponent : public ComponentData<MyTransformComponent> {
	sf::Vector3f Location, Scale;
	float Angle;
	MyTransformComponent* parent;
};
