#include "Collision.h"
#include <cmath>

CollisionSphere::CollisionSphere(Vec2D _Position, float _Radius)
{
	ShapeType = CollisionShape::Sphere;
}

CollisionTriangle::CollisionTriangle(Vec2D _Position_v1, Vec2D _Position_v2, Vec2D _Position_v3)
{
	ShapeType = CollisionShape::Triangle;

	v1 = _Position_v1;
	v2 = _Position_v2;
	v3 = _Position_v3;
}

void CollisionTriangle::CollisionDetection_SphereSphere(Collision* OtherCollision, HitResult& OutputHitResult)
{
}

void CollisionTriangle::CollisionDetection_SphereTriangle(Collision* OtherCollision, HitResult& OutputHitResult)
{
}

void Collision::CollisionDetection(Collision* OtherCollision, HitResult& OutputHitResult)
{
	if (ShapeType == CollisionShape::Sphere)
	{
		if (OtherCollision->ShapeType == CollisionShape::Sphere)
		{
			CollisionDetection_SphereSphere(OtherCollision, OutputHitResult);
		}
		else if (OtherCollision->ShapeType == CollisionShape::Triangle)
		{
			CollisionDetection_SphereTriangle(OtherCollision, OutputHitResult);
		}
	}
}

void CollisionSphere::CollisionDetection_SphereSphere(Collision* OtherCollision, HitResult& OutputHitResult)
{
	CollisionSphere* Other = dynamic_cast<CollisionSphere*>(OtherCollision);

	float Dist = sqrt((Position.X - Other->Position.X) * (Position.X - Other->Position.X) + (Position.Y - Other->Position.Y) * (Position.Y - Other->Position.Y));
	if (Dist <= Radius + Other->Radius) {
		float Scalar = (Velocity.X - Other->Velocity.X) * (Position.X - Other->Position.X) + (Velocity.Y - Other->Velocity.Y) * (Position.Y - Other->Position.Y);
		float Koeff = 2.0 * Other->Mas / (Mas + Other->Mas) * Scalar / (Dist * Dist);
		float newV1_x = Velocity.X - Koeff * (Position.X - Other->Position.X);
		float newV1_y = Velocity.Y - Koeff * (Position.Y - Other->Position.Y);

		Scalar = (Other->Velocity.X - Velocity.X) * (Other->Position.X - Position.X) + (Other->Velocity.Y - Velocity.Y) * (Other->Position.Y - Position.Y);
		Koeff = 2.0 * Mas / (Mas + Other->Mas) * Scalar / (Dist * Dist);
		float newV2_x = Other->Velocity.X - Koeff * (Other->Position.X - Position.X);
		float newV2_y = Other->Velocity.Y - Koeff * (Other->Position.Y - Position.Y);

		Velocity.X = newV1_x;
		Velocity.Y = newV1_y;

		Other->Velocity.X = newV2_x;
		Other->Velocity.Y = newV2_y;
	}
}

void CollisionSphere::CollisionDetection_SphereTriangle(Collision* OtherCollision, HitResult& OutputHitResult)
{

}