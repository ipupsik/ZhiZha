#pragma once

#include <memory>
#include <unordered_map>

#include "Component.h"

class Entity {
	friend class EntityManager;
	friend struct std::hash<Entity>;
	friend struct std::equal_to<Entity>;

private:
	std::unordered_map<size_t, std::shared_ptr<Component>> _components;

	const Entity* _parent;

	Entity copy() const;

public:
	Entity();

	friend bool operator==(const Entity& lhs, const Entity& rhs) {
		return lhs._components == rhs._components
			&& lhs._parent == rhs._parent;
	}

	[[nodiscard]] std::shared_ptr<TransformComponent> Transform() const;

	[[nodiscard]] const Entity* GetParent() const;
};

template <>
struct std::hash<Entity> {
	size_t operator()(const Entity& actor) const noexcept {
		std::size_t hash = std::hash<const Entity*>{}(actor._parent);
		int i = 1;
		for (const auto& element : actor._components)
			hash ^= std::hash<std::shared_ptr<Component>>{}(element.second) << i++;

		return hash;
	}
};
