#include "Entity.h"

const Entity& Entity::GetParent() const {
	return *_parent;
}

Entity::Entity(): _parent(nullptr), _id(_count++) {
}

Entity* Entity::copy() const {
	const auto copy = new Entity();
	copy->_parent = this;
	return copy;
}

std::atomic_size_t Entity::_count = 0;