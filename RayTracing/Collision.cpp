#include "Collision.h"

Collision::Collision(Vec3D _Position) : Position(_Position)
{
	
}

CollisionSphere::CollisionSphere(Vec3D _Position, float _Radius) : Collision::Collision(_Position),
	Radius(_Radius)
{
	ShapeType = CollisionShape::Sphere;
}

CollisionBox::CollisionBox(Vec3D _Position, Vec3D _Scale, Vec3D _Rotation) : Collision::Collision(_Position),
	Scale(_Scale), Rotation(_Rotation)
{
	ShapeType = CollisionShape::Box;
}

CollisionCapsule::CollisionCapsule(Vec3D _Position, Vec3D _Rotation, float _Radius, float _Height) : Collision::Collision(_Position),
	Radius(_Radius), Height(_Height), Rotation(_Rotation)
{
	ShapeType = CollisionShape::Capsule;
}

void Collision::CollisionDetection(Collision* OtherCollision, HitResult& OutputHitResult)
{
	if (ShapeType == CollisionShape::Sphere)
	{
		if (ShapeType == CollisionShape::Sphere)
		{
			CollisionDetection_SphereSphere(OtherCollision, OutputHitResult);
		}
		else if (ShapeType == CollisionShape::Box)
		{
			CollisionDetection_SphereBox(OtherCollision, OutputHitResult);
		}
	}
	else if (ShapeType == CollisionShape::Box)
	{
		if (ShapeType == CollisionShape::Sphere)
		{
			CollisionDetection_SphereBox(OtherCollision, OutputHitResult);
		}
		else if (ShapeType == CollisionShape::Box)
		{
			CollisionDetection_BoxBox(OtherCollision, OutputHitResult);
		}
	}
	else if (/*Капсула тут, но пока забью хуяку*/ false);
}

void Collision::CollisionDetection_SphereSphere(Collision* OtherCollision, HitResult& OutputHitResult)
{
	
}

void Collision::CollisionDetection_SphereBox(Collision* OtherCollision, HitResult& OutputHitResult)
{

}

void Collision::CollisionDetection_BoxBox(Collision* OtherCollision, HitResult& OutputHitResult)
{

}
