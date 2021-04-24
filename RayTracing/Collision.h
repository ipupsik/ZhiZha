#pragma once

#include "HitResult.h"
#include "PupsyaEnums.h"
#include "PupsyaTypes.h"

class Actor;

class Collision
{
public:
	Collision();
	Collision(Actor* parent);

	void CollisionDetection(Collision* OtherCollision, HitResult& OutputHitResult);

	virtual void CollisionDetection_SphereSphere(Collision* OtherCollision, HitResult& OutputHitResult) = 0;
	virtual void CollisionDetection_SphereTriangle(Collision* OtherCollision, HitResult& OutputHitResult) = 0;

	virtual void UpdatePhysicState(float DeltaSeconds) = 0;

	Vec2D Velocity, Acceleration;

	float Mas;

	CollisionShape ShapeType;
	Actor* Parent;
};

class CollisionSphere : public Collision
{
public:
	CollisionSphere(Vec2D _Position, float _Radius, Actor* parent);

	void CollisionDetection_SphereSphere(Collision* OtherCollision, HitResult& OutputHitResult) override;
	void CollisionDetection_SphereTriangle(Collision* OtherCollision, HitResult& OutputHitResult) override;

	void UpdatePhysicState(float DeltaSeconds) override;

	Vec2D Position;
	float Radius;
};

class CollisionTriangle : public Collision
{
public:
	CollisionTriangle(Vec2D _Position_v1, Vec2D _Position_v2, Vec2D _Position_v3, Actor* parent);

	void CollisionDetection_SphereSphere(Collision* OtherCollision, HitResult& OutputHitResult) override;
	void CollisionDetection_SphereTriangle(Collision* OtherCollision, HitResult& OutputHitResult) override;

	void UpdatePhysicState(float DeltaSeconds) override;

	Vec2D v1, v2, v3;
};