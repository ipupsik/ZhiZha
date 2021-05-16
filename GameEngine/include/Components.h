#pragma once

#include <string>
#include <SFML/Graphics/Color.hpp>

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

struct ComplexCollision : public ComponentData<ComplexCollision> {
};

struct RenderComponent : public ComponentData<RenderComponent> {
	sf::Color color;
};

struct HugeComponent: public ComponentData<HugeComponent> {
	std::size_t Index;
};