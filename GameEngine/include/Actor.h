#pragma once

#include <vector>
#include <memory>
#include <SFML/System/String.hpp>
#include <unordered_set>
#include <unordered_map>
#include <typeinfo>

#include "Component.h"

class Actor {
  friend class ActorManager;

 private:
  std::unordered_map<size_t, std::shared_ptr<Component>> _components;

  std::weak_ptr<Actor> _parent;

  std::shared_ptr<TransformComponent> _transform;

 public:
  Actor();

  [[nodiscard]] std::shared_ptr<TransformComponent> Transform() const;

  [[nodiscard]] const std::weak_ptr<Actor> &GetParent() const;
};

