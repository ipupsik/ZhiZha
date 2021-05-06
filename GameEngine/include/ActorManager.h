#pragma once

#include <SFML/System/Vector2.hpp>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <functional>

#include "Actor.h"
#include "ActorArchetype.h"
#include "Component.h"

class ActorManager {
  std::unordered_map<size_t, std::unordered_set<Actor>> _actors;

  ActorManager();

  template<std::derived_from<Component> T, typename ...Args>
  std::shared_ptr<T> addComponent(Actor &actor, Args &&...args) {
      auto component = std::make_shared<T>(std::forward<Args>(args)...);
      _actors.try_emplace(component->Type());
      _actors[component->Type()].emplace(actor);
      actor._components[component->Type()] = component;
      return std::dynamic_pointer_cast<T>(component);
  }

 public:
  std::unordered_set<Actor> GetActors() const;

  template<std::derived_from<Component> Component>
  auto GetActorsBy() const {
      if (_actors.contains(typeid(Component).hash_code()))
          return _actors.at(typeid(Component).hash_code());
      return std::unordered_set<Actor>();
  }

  Actor CreateActor();

  Actor Instantiate(const Actor &parent);

  Actor Instantiate(const Actor &parent, sf::Vector2f position);

  Actor FromArchetype(ActorArchetype &&archetype);

  template<std::derived_from<Component> T>
  std::shared_ptr<T> GetComponent(const Actor &actor) const {
      if (!actor._components.contains(typeid(T).hash_code()))
          return nullptr;
      else
          return std::dynamic_pointer_cast<T>(actor._components.at(typeid(T).hash_code()));
  }

  template<std::derived_from<Component> T, std::convertible_to<std::function<T()>> Func>
  std::shared_ptr<T> GetOrAddComponent(Actor &actor, Func f) {
      auto cmp = GetComponent<T>(actor);
      if (!cmp)
          return addComponent<T>(actor, f());
      return cmp;
  }

  template<std::derived_from<Component> T>
  std::shared_ptr<T> GetOrAddComponent(Actor &actor, T cmp) {
      return GetOrAddComponent<T>(actor, [&] {
        return cmp;
      });
  }

  template<std::derived_from<Component> T>
  bool RemoveComponent(Actor &actor) {
      auto cmp = GetComponent<T>(actor);
      if (!cmp) return false;
      _actors[typeid(T).hash_code()].erase(actor);
      actor._components.erase(cmp->Type());
      return true;
  }

  template<std::derived_from<Component> T>
  bool HasComponent(const Actor &actor) const {
      return GetComponent<T>(actor) != nullptr;
  }

  static ActorManager Current;
};
