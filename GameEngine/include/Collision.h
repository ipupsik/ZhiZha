#pragma once

#include <memory>

#include "HitResult.h"
#include "PupsyaEnums.h"
#include "PupsyaTypes.h"

class Actor;

class Collision
{
public:
	Collision();
	Collision(std::weak_ptr<Actor> parent);

	void CollisionDetection(std::unique_ptr<Collision> OtherCollision, HitResult& OutputHitResult);

	virtual void CollisionDetection_SphereSphere(std::unique_ptr<Collision> OtherCollision, HitResult& OutputHitResult) = 0;
	virtual void CollisionDetection_SphereTriangle(std::unique_ptr<Collision> OtherCollision, HitResult& OutputHitResult) = 0;

	virtual void UpdatePhysicState(float DeltaSeconds) = 0;

	Vec2D Velocity, Acceleration;

	float Mas;

	CollisionShape ShapeType;
	std::weak_ptr<Actor> Parent;
};

class CollisionSphere : public Collision
{
public:
	CollisionSphere(Vec2D _Position, float _Radius, std::weak_ptr<Actor> parent);

	void CollisionDetection_SphereSphere(std::unique_ptr<Collision> OtherCollision, HitResult& OutputHitResult) override;
	void CollisionDetection_SphereTriangle(std::unique_ptr<Collision> OtherCollision, HitResult& OutputHitResult) override;

	void UpdatePhysicState(float DeltaSeconds) override;

	Vec2D Position;
	float Radius;
};

class CollisionTriangle : public Collision
{
public:
	CollisionTriangle(Vec2D _Position_v1, Vec2D _Position_v2, Vec2D _Position_v3, std::weak_ptr<Actor> parent);

	void CollisionDetection_SphereSphere(std::unique_ptr<Collision> OtherCollision, HitResult& OutputHitResult) override;
	void CollisionDetection_SphereTriangle(std::unique_ptr<Collision> OtherCollision, HitResult& OutputHitResult) override;

	void UpdatePhysicState(float DeltaSeconds) override;

	Vec2D v1, v2, v3;
};