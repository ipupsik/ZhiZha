#include "Actor.h"

std::shared_ptr<TransformComponent> Actor::Transform() const {
    return std::dynamic_pointer_cast<TransformComponent>(_components.at(typeid(TransformComponent).hash_code()));
}

const Actor *Actor::GetParent() const {
    return _parent;
}

Actor::Actor(): _parent(nullptr) {
}

Actor Actor::copy() const {
    auto copy = Actor();
    for(const auto& [type, component]: _components)
        copy._components[type] = component->Copy();
    copy._parent = this;
    return copy;
}