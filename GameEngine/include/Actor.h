#pragma once

#include <vector>
#include <memory>
#include <SFML/System/String.hpp>

#include "StaticMesh.h"
#include "Material.h"
#include "Collision.h"

class Collision;

class Actor : private std::enable_shared_from_this<Actor> { // for safe use of std::shared_ptr(this)
 public:
  Actor();

  void InitMesh(const sf::String& filename);

  void InitMesh(std::unique_ptr<StaticMesh> Other);

  virtual void BeginPlay();

  virtual void Tick(float DeltaSeconds);

  virtual void Draw();

  void MakeComplexCollision();

  Vec2D Location, Rotation, Scale;
  Vec2D Velocity, Acceleration;

  void InitMaterialShader(const sf::String& filename);

 public:
  std::unique_ptr<StaticMesh> Mesh;
  std::unique_ptr<Material> Mat;
  std::vector<std::unique_ptr<Collision>> Collider;

  std::weak_ptr<Actor> Parent;
};

