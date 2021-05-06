#include "ActorManager.h"

ActorManager ActorManager::Current = ActorManager();

Actor ActorManager::Instantiate(const Actor& parent, const sf::Vector2f position) {
	auto copy = parent.copy();

	copy.Transform()->Location = position;
	for (const auto& [type, component] : copy._components) {
		_actors.try_emplace(type);
		_actors[type].emplace(copy);
	}
	return std::forward<Actor>(copy);
}

Actor ActorManager::FromArchetype(ActorArchetype&& archetype) {
	auto actor = CreateActor();

	for (const auto& component : archetype.GetComponents()) {
		_actors.try_emplace(component->Type());
		_actors[component->Type()].emplace(actor);
		actor._components.emplace(component->Type(), component->Copy());
	}
	return actor;
}

Actor ActorManager::Instantiate(const Actor& parent) {
	return Instantiate(parent, parent.Transform()->Location);
}

Actor ActorManager::CreateActor() {
	auto basic = Actor();
	addComponent<TransformComponent>(basic, TransformComponent({0, 0}, {0, 0}, {1, 1}));
	return basic;
}

std::unordered_set<Actor> ActorManager::GetActors() const {
	decltype(GetActors()) result;
	for (const auto& [k, v] : _actors)
		result.insert(v.begin(), v.end());
	return result;
}

ActorManager::ActorManager() = default;
