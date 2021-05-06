#pragma once

#include <SFML/System/Vector2.hpp>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <functional>

#include "Entity.h"
#include "Component.h"

class EntityManager {
	std::unordered_map<size_t, std::unordered_set<Entity>> _actors;

	EntityManager();

	template <std::derived_from<Component> T, typename ...Args>
	std::shared_ptr<T> addComponent(Entity& actor, Args&&...args) {
		auto component = std::make_shared<T>(std::forward<Args>(args)...);
		_actors.try_emplace(T::Type);
		_actors[T::Type].emplace(actor);
		actor._components[T::Type] = component;
		return std::dynamic_pointer_cast<T>(component);
	}

public:
	[[nodiscard]] std::unordered_set<Entity> GetActors() const;

	template <std::derived_from<Component> T>
	auto GetActorsBy() const {
		if (_actors.contains(TypeFamily<Component>::Type<T>()))
			return _actors.at(TypeFamily<Component>::Type<T>());
		return std::unordered_set<Entity>();
	}

	Entity CreateEntity();

	Entity Instantiate(const Entity& parent);

	Entity Instantiate(const Entity& parent, sf::Vector2f position);

	template <std::derived_from<Component> T>
	std::shared_ptr<T> GetComponent(const Entity& actor) const {
		if (!actor._components.contains(TypeFamily<Component>::Type<T>()))
			return nullptr;
		return std::dynamic_pointer_cast<T>(actor._components.at(TypeFamily<Component>::Type<T>()));
	}

	template <std::derived_from<Component> T, std::convertible_to<std::function<T()>> Func>
	std::shared_ptr<T> GetOrAddComponent(Entity& actor, Func f) {
		auto cmp = GetComponent<T>(actor);
		if (!cmp)
			return addComponent<T>(actor, f());
		return cmp;
	}

	template <std::derived_from<Component> T>
	std::shared_ptr<T> GetOrAddComponent(Entity& actor, T cmp) {
		return GetOrAddComponent<T>(actor, [&] {
			return cmp;
		});
	}

	template <std::derived_from<Component> T>
	bool RemoveComponent(Entity& actor) {
		auto cmp = GetComponent<T>(actor);
		if (!cmp) return false;
		_actors[TypeFamily<Component>::Type<T>()].erase(actor);
		actor._components.erase(T::Type);
		return true;
	}

	template <std::derived_from<Component> T>
	[[nodiscard]] bool HasComponent(const Entity& actor) const {
		return GetComponent<T>(actor) != nullptr;
	}

	static EntityManager Current;
};
