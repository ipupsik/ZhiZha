#pragma once

#include "HitResult.h"
#include "PupsyaEnums.h"
#include "PupsyaTypes.h"

class Collision
{
public:
	void CollisionDetection(Collision* OtherCollision, HitResult& OutputHitResult);

	virtual void CollisionDetection_SphereSphere(Collision* OtherCollision, HitResult& OutputHitResult) = 0;
	virtual void CollisionDetection_SphereTriangle(Collision* OtherCollision, HitResult& OutputHitResult) = 0;

	Vec2D Velocity, Acceleration;

	float Mas;

	CollisionShape ShapeType;
};

class CollisionSphere : public Collision
{
public:
	CollisionSphere(Vec2D _Position, float _Radius);

	void CollisionDetection_SphereSphere(Collision* OtherCollision, HitResult& OutputHitResult) override;
	void CollisionDetection_SphereTriangle(Collision* OtherCollision, HitResult& OutputHitResult) override;

	Vec2D Position;
	float Radius;
};

class CollisionTriangle : public Collision
{
public:
	CollisionTriangle(Vec2D _Position_v1, Vec2D _Position_v2, Vec2D _Position_v3);

	void CollisionDetection_SphereSphere(Collision* OtherCollision, HitResult& OutputHitResult) override;
	void CollisionDetection_SphereTriangle(Collision* OtherCollision, HitResult& OutputHitResult) override;

	Vec2D v1, v2, v3;
};