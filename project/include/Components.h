#pragma once

#include <string>

#include "Component.h"
#include "SFML/System/Vector2.hpp"

struct TestComponent : public ComponentData<TestComponent> {
	int Data;
};

struct NameComponent : public ComponentData<NameComponent> {
	std::string Name;
};

struct TransformComponent : public ComponentData<TransformComponent> {
	sf::Vector2f Location, Rotation, Scale;
};
