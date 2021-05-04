#include "Actor.h"

//FIXME glfw -> sfml

std::shared_ptr<TransformComponent> Actor::Transform() const {
    return _transform;
}

const std::weak_ptr<Actor> &Actor::GetParent() const {
    return _parent;
}

Actor::Actor() : _transform(std::make_shared<TransformComponent>(
    TransformComponent({0, 0}, {0, 0}, {1, 1}))) {
    _components.emplace(_transform);
}