#pragma once

#include <SFML/System/Vector2.hpp>
#include <memory>
#include <ranges>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include "Actor.h"
#include "Component.h"

class ActorManager {
  using Actor_p = std::shared_ptr<Actor>;

  std::unordered_map<size_t, std::unordered_set<Actor_p>> _actors;

  ActorManager();

  template<std::derived_from<Component> T, typename ...Args>
  std::shared_ptr<T> AddComponent(const Actor_p &actor, Args &&...args) {
      const auto &cmp = std::make_shared<T>(std::forward<Args>(args)...);
      _actors.try_emplace(cmp->Type(), std::unordered_set<std::shared_ptr<Component>>());
      _actors[cmp->Type()].emplace(actor);
      actor->_components[cmp->Type()] = cmp;
      return cmp;
  }

 public:
  std::vector<Actor_p> GetActors();

  template<std::derived_from<Component> Component>
  auto GetActorsBy() {
      if (_actors.contains(typeid(Component).hash_code()))
          return _actors[typeid(Component).hash_code()];
      return std::unordered_set<Actor_p>();
  }

  std::shared_ptr<Actor> CreateActor();

  std::shared_ptr<Actor> Instantiate(const Actor_p &parent);

  std::shared_ptr<Actor> Instantiate(const Actor_p &parent, sf::Vector2f position);

  template<std::derived_from<Component> T>
  std::shared_ptr<T> GetComponent(const Actor_p &actor) {
      if (!_actors.contains(typeid(T).hash_code()))
          return nullptr;
      return std::dynamic_pointer_cast<T>(actor->_components[typeid(T).hash_code()]);
  }

  template<std::derived_from<Component> T, std::convertible_to<std::function<T()>> Func>
  std::shared_ptr<T> GetOrAddComponent(const Actor_p &actor, Func f) {
      auto cmp = GetComponent<T>(actor);
      if (!cmp)
          return AddComponent<T>(actor, f());
      return cmp;
  }

  template<std::derived_from<Component> T>
  std::shared_ptr<T> GetOrAddComponent(const Actor_p &actor, T cmp) {
      return GetOrAddComponent<T>(actor, [&] {
        return cmp;
      });
  }

  template<std::derived_from<Component> T>
  bool RemoveComponent(const Actor_p &actor) {
      auto cmp = GetComponent<T>();
      if (!cmp) return false;
      _actors[typeid(T).hash_code()].erase(actor);
      actor->_components.erase(cmp);
      return true;
  }

  static ActorManager Current;
};