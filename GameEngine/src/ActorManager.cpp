#include "ActorManager.h"

ActorManager ActorManager::Current = ActorManager();

std::shared_ptr<Actor> ActorManager::Instantiate(const std::shared_ptr<Actor>& parent,
                                                 const sf::Vector2f position) {
	auto copy = std::make_shared<Actor>(Actor(*parent));
	
	copy->Transform()->Location = position;
	copy->_parent = parent;
	for (const auto& component : copy->_components | std::views::values) {
		std::cout << component->Type() << std::endl;
		_actors.try_emplace(component->Type(), std::unordered_set<decltype(copy)>());
		_actors[component->Type()].emplace(copy);
	}
	return copy;
}

std::shared_ptr<Actor> ActorManager::Instantiate(const std::shared_ptr<Actor>& parent) {
	return Instantiate(parent, parent->Transform()->Location);
}

std::shared_ptr<Actor> ActorManager::CreateActor() {
	const auto basic = std::make_shared<Actor>();
	basic->_transform = AddComponent<TransformComponent>(basic, TransformComponent({ 0, 0 }, { 0, 0 }, { 1, 1 }));
	return basic;
}

std::vector<std::shared_ptr<Actor>> ActorManager::GetActors() {
	decltype(GetActors()) result;
	for (const auto& v : _actors | std::views::values)
		result.insert(result.end(), v.begin(), v.end());
	return result;
}

ActorManager::ActorManager() = default;
