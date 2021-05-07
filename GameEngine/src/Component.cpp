#include "Component.h"

TransformComponent::TransformComponent(sf::Vector2f location,
                                       sf::Vector2f rotation,
                                       sf::Vector2f scale)
	: Location(location), Rotation(rotation), Scale(scale) {}

std::shared_ptr<Component> TransformComponent::Copy() {
	return std::make_shared<TransformComponent>(*this);
}
