#include "Actor.h"

//FIXME glfw -> sfml

std::shared_ptr<TransformComponent> Actor::Transform() const {
	return _transform;
}

const std::weak_ptr<Actor>& Actor::GetParent() const {
	return _parent;
}

Actor::Actor() {
}
