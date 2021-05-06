#pragma once

#include <memory>
#include <unordered_map>

#include "Component.h"

class Actor {
	friend class ActorManager;
	friend struct std::hash<Actor>;
	friend struct std::equal_to<Actor>;

private:
	std::unordered_map<size_t, std::shared_ptr<Component>> _components;

	const Actor* _parent;

	Actor copy() const;

public:
	Actor();

	friend bool operator==(const Actor& lhs, const Actor& rhs) {
		return lhs._components == rhs._components
			&& lhs._parent == rhs._parent;
	}

	[[nodiscard]] std::shared_ptr<TransformComponent> Transform() const;

	[[nodiscard]] const Actor* GetParent() const;
};

template <>
struct std::hash<Actor> {
	size_t operator()(const Actor& actor) const noexcept {
		std::size_t hash = std::hash<const Actor*>{}(actor._parent);
		int i = 1;
		for (const auto& element : actor._components)
			hash ^= std::hash<std::shared_ptr<Component>>{}(element.second) << i++;

		return hash;
	}
};
