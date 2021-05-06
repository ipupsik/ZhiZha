#include "Component.h"

#include <utility>

TransformComponent::TransformComponent(sf::Vector2f location,
                                       sf::Vector2f rotation,
                                       sf::Vector2f scale)
	: Location(location), Rotation(rotation), Scale(scale) {}

size_t TransformComponent::Type() {
	return typeid(*this).hash_code();
}

size_t TestComponent::Type() {
	return typeid(*this).hash_code();
}

TestComponent::TestComponent(int data): Data(data) {}

NameComponent::NameComponent(std::string name): Name(std::move(name)) {}

size_t NameComponent::Type() {
	return typeid(*this).hash_code();
}
