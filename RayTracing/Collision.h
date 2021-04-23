#ifndef _H_COLLISION_
#define _H_COLLISION_

#include "HitResult.h"
#include "PupsyaEnums.h"
#include "PupsyaTypes.h"

class Collision
{
public:

	void CollisionDetection(Collision* OtherCollision, HitResult& OutputHitResult);

	void CollisionDetection_SphereSphere(Collision* OtherCollision, HitResult& OutputHitResult);
	void CollisionDetection_SphereBox(Collision* OtherCollision, HitResult& OutputHitResult);
	void CollisionDetection_BoxBox(Collision* OtherCollision, HitResult& OutputHitResult);

	Collision(Vec3D _Position);

	Vec3D Position;

	CollisionShape ShapeType;
};

class CollisionSphere : public Collision
{
public:
	CollisionSphere(Vec3D _Position, float _Radius);

	float Radius;
};

class CollisionBox : public Collision
{
public:
	CollisionBox(Vec3D _Position, Vec3D _Scale, Vec3D _Rotation);

	Vec3D Scale, Rotation;
};

class CollisionCapsule : public Collision
{
public:
	CollisionCapsule(Vec3D _Position, Vec3D _Rotation, float _Radius, float _Height);

	float Radius, Height;
	Vec3D Rotation;
};

#endif