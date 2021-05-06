#pragma once
#include <memory>
#include <vector>

#include "Component.h"

class ActorArchetype {
	std::vector<std::unique_ptr<Component>> _components;

public:
	[[nodiscard]] const std::vector<std::unique_ptr<Component>>& GetComponents() const { return _components; }

	explicit ActorArchetype(const std::vector<Component*>&  components);
};
