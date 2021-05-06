#include "Entity.h"

std::shared_ptr<TransformComponent> Entity::Transform() const {
	return std::dynamic_pointer_cast<TransformComponent>(
		_components.at(TypeFamily<Component>::Type<TransformComponent>()));
}

const Entity* Entity::GetParent() const {
	return _parent;
}

Entity::Entity(): _parent(nullptr) {}

Entity Entity::copy() const {
	auto copy = Entity();
	for (const auto& [type, component] : _components)
		copy._components[type] = component->Copy();
	copy._parent = this;
	return copy;
}
