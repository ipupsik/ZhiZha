#pragma once

#include <memory>

#include "HitResult.h"
#include "PupsyaEnums.h"

class Entity;

class Collision {
public:
	Collision();
	Collision(std::weak_ptr<Entity> parent);

	void CollisionDetection(std::shared_ptr<Collision> OtherCollision, HitResult& OutputHitResult);

	virtual void CollisionDetection_SphereSphere(std::shared_ptr<Collision> OtherCollision, HitResult& OutputHitResult)
	= 0;
	virtual void CollisionDetection_SphereTriangle(std::shared_ptr<Collision> OtherCollision,
	                                               HitResult& OutputHitResult) = 0;

	virtual void UpdatePhysicState(float DeltaSeconds) = 0;

	sf::Vector2f Velocity, Acceleration;

	float Mas;

	CollisionShape ShapeType;
	std::weak_ptr<Entity> Parent;
};

class CollisionSphere : public Collision, private std::enable_shared_from_this<CollisionSphere> {
public:
	CollisionSphere(sf::Vector2f _Position, float _Radius, std::weak_ptr<Entity> parent);

	void CollisionDetection_SphereSphere(std::shared_ptr<Collision> OtherCollision,
	                                     HitResult& OutputHitResult) override;
	void CollisionDetection_SphereTriangle(std::shared_ptr<Collision> otherCollision,
	                                       HitResult& outputHitResult) override;

	void UpdatePhysicState(float DeltaSeconds) override;

	sf::Vector2f Position;
	float Radius;
};

class CollisionTriangle : public Collision {
public:
	CollisionTriangle(sf::Vector2f _Position_v1, sf::Vector2f _Position_v2, sf::Vector2f _Position_v3,
	                  std::weak_ptr<Entity> parent);

	void CollisionDetection_SphereSphere(std::shared_ptr<Collision> OtherCollision,
	                                     HitResult& OutputHitResult) override;
	void CollisionDetection_SphereTriangle(std::shared_ptr<Collision> OtherCollision,
	                                       HitResult& OutputHitResult) override;

	void UpdatePhysicState(float DeltaSeconds) override;

	sf::Vector2f v1, v2, v3;
};
