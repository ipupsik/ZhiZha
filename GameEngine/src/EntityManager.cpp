#include "EntityManager.h"

EntityManager EntityManager::Current = EntityManager();

Entity EntityManager::Instantiate(const Entity& parent, const sf::Vector2f position) {
	auto copy = parent.copy();

	copy.Transform()->Location = position;
	for (const auto& [type, component] : copy._components) {
		_actors.try_emplace(type);
		_actors[type].emplace(copy);
	}
	return std::forward<Entity>(copy);
}

Entity EntityManager::Instantiate(const Entity& parent) {
	return Instantiate(parent, parent.Transform()->Location);
}

Entity EntityManager::CreateEntity() {
	auto basic = Entity();
	addComponent<TransformComponent>(basic, TransformComponent({0, 0}, {0, 0}, {1, 1}));
	return basic;
}

std::unordered_set<Entity> EntityManager::GetActors() const {
	decltype(GetActors()) result;
	for (const auto& [k, v] : _actors)
		result.insert(v.begin(), v.end());
	return result;
}

EntityManager::EntityManager() = default;
