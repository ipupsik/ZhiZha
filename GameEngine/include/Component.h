#pragma once

#include <SFML/System/Vector2.hpp>
#include <string>
#include <typeinfo>

class Component {
 public:
  virtual size_t Type() = 0;
};

struct TransformComponent: public Component {
  sf::Vector2f Location, Rotation, Scale;

  TransformComponent(sf::Vector2f location, sf::Vector2f rotation, sf::Vector2f scale);

  size_t Type() override;
};

struct TestComponent: public Component {
  int Data;

  explicit TestComponent(int data);

  size_t Type() override;
};