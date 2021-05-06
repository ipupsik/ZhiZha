#include "ActorArchetype.h"

ActorArchetype::ActorArchetype(const std::vector<Component *> &components) {
    for (const auto &component : components) {
        _components.emplace_back(component);
    }
}
