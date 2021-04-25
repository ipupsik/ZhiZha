#include "Collision.h"
#include <cmath>
#include "Actor.h"

Collision::Collision()
{

}

Collision::Collision(Actor* parent)
{
	Parent = parent;
}

CollisionSphere::CollisionSphere(Vec2D _Position, float _Radius, Actor* parent) : Collision(parent)
{
	ShapeType = CollisionShape::Sphere;

	Velocity = { 0,0 };
	Acceleration = { 0, 0 };
	Position = _Position;
	Radius = _Radius;
}

CollisionTriangle::CollisionTriangle(Vec2D _Position_v1, Vec2D _Position_v2, Vec2D _Position_v3, Actor* parent) : Collision(parent)
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

void CollisionTriangle::UpdatePhysicState(float DeltaSeconds)
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

void CollisionSphere::UpdatePhysicState(float DeltaSeconds)
{
	Position.X += Velocity.X + Acceleration.X * DeltaSeconds * DeltaSeconds / 2;
	Position.Y += Velocity.Y + Acceleration.Y * DeltaSeconds * DeltaSeconds / 2;

	Velocity.X += Acceleration.X * DeltaSeconds;
	Velocity.Y += Acceleration.Y * DeltaSeconds;
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

Vec2D find_parent_position(Collision* Collision)
{
	Actor* parent = Collision->Parent;
	Vec2D pos = { 0, 0 };

	while (parent)
	{
		pos = pos + parent->Location;

		parent = parent->Parent;
	}

	return pos;
}

void CollisionSphere::CollisionDetection_SphereTriangle(Collision* OtherCollision, HitResult& OutputHitResult)
{
	CollisionTriangle* OtherTriangle = dynamic_cast<CollisionTriangle*>(OtherCollision);

	Vec2D pos_parent_triangle = find_parent_position(OtherTriangle);
	Vec2D pos_parent_my = find_parent_position(this);

	Vec2D vec12 = OtherTriangle->v2 - OtherTriangle->v1;
	Vec2D vec13 = OtherTriangle->v3 - OtherTriangle->v1;
	Vec2D vec23 = OtherTriangle->v3 - OtherTriangle->v2;
	Vec2D vec10 = Position + pos_parent_my - OtherTriangle->v1 - pos_parent_triangle;
	Vec2D vec20 = Position + pos_parent_my - OtherTriangle->v2 - pos_parent_triangle;
	Vec2D vec30 = Position + pos_parent_my - OtherTriangle->v3 - pos_parent_triangle;

	float cos_012 = vec12.Dot(vec10) / vec12.Length() / vec10.Length();
	float cos_021 = (vec12 * -1).Dot(vec20) / vec12.Length() / vec20.Length();

	float cos_013 = vec13.Dot(vec10) / vec13.Length() / vec10.Length();
	float cos_031 = (vec13 * -1).Dot(vec30) / vec13.Length() / vec30.Length();

	float cos_023 = vec23.Dot(vec20) / vec23.Length() / vec20.Length();
	float cos_032 = (vec23 * -1).Dot(vec30) / vec23.Length() / vec30.Length();

	float h_12 = fabs(sqrt(pow(vec10.Length(), 2) - pow(cos_012 * vec10.Length(),2)));
	float h_13 = fabs(sqrt(pow(vec10.Length(), 2) - pow(cos_013 * vec10.Length(),2)));
	float h_23 = fabs(sqrt(pow(vec20.Length(), 2) - pow(cos_023 * vec20.Length(),2)));

	float min_h;
	Vec2D min_line;
	Vec2D min_dist_to_center;

	bool does_hit = false;

	if (cos_012 >= 0 && cos_021 >= 0)
	{
		min_h = h_12;
		min_line = vec12;
		min_dist_to_center = vec10;

		does_hit = true;
	}

	if (cos_013 >= 0 && cos_031 >= 0)
	{
		if (!does_hit || h_13 < min_h)
		{
			min_h = h_13;
			min_line = vec13;
			min_dist_to_center = vec10;

			does_hit = true;
		}
	}

	if (cos_023 >= 0 && cos_032 >= 0)
	{
		if (!does_hit || h_23 < min_h)
		{
			min_h = h_23;
			min_line = vec23;
			min_dist_to_center = vec20;

			does_hit = true;
		}
	}

	if (does_hit && min_h < Radius)
	{
		Vec2D n = (min_line.Cross(min_line.Cross(min_dist_to_center))).Normalize();

		float alpha_double = 2 * acos(min_line.Dot(n) / n.Length() / min_line.Length());

		Vec2D new_velocity = {cos(alpha_double) * Velocity.X - sin(alpha_double) * Velocity.Y,
							  sin(alpha_double) * Velocity.X + cos(alpha_double) * Velocity.Y};

		//Velocity = new_velocity;
		Velocity = { 0, 0 };
	}
}