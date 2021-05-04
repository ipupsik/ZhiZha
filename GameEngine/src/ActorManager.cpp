#include <ActorManager.h>

ActorManager ActorManager::Current = ActorManager();

std::shared_ptr<Actor> ActorManager::Instantiate(const std::shared_ptr<Actor> &parent,
                                                 sf::Vector2f position) {
    auto copy = std::make_shared<Actor>(Actor(*parent));
    copy->Transform()->Location = position;
    copy->_parent = parent;
    for (const auto& cmp : copy->_components) {
        std::cout << cmp.second->Type() << std::endl;
        _actors.try_emplace(cmp.second->Type(), std::unordered_set<decltype(copy)>());
        _actors[cmp.second->Type()].emplace(copy);
    }
    return copy;
}

std::shared_ptr<Actor> ActorManager::Instantiate(const std::shared_ptr<Actor> &parent) {
    return Instantiate(parent, parent->Transform()->Location);
}

std::shared_ptr<Actor> ActorManager::CreateActor() {
    return Instantiate(std::make_shared<Actor>(Actor()));
}

std::vector<std::shared_ptr<Actor>> ActorManager::GetActors() {
    decltype(GetActors()) result;
    for(const auto& [_, v] : _actors)
        result.insert(result.end(), v.begin(), v.end());
    return result;
}

ActorManager::ActorManager() = default;
