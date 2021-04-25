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

	float eps = 0.000001;
	float inf = 50000;

	// поиск мировых координат родителей вершин
	Vec2D pos_parent_triangle = find_parent_position(OtherTriangle);
	Vec2D pos_parent_my = find_parent_position(this);

	// Перевод вершин в мировые координаты
	Vec2D world_pos_v1 = OtherTriangle->v1 + pos_parent_triangle;
	Vec2D world_pos_v2 = OtherTriangle->v2 + pos_parent_triangle;
	Vec2D world_pos_v3 = OtherTriangle->v3 + pos_parent_triangle;
	Vec2D world_pos_circle = Position + pos_parent_my;

	// составление векторов-сторон треугольника
	Vec2D vec12 = world_pos_v2 - world_pos_v1;
	Vec2D vec13 = world_pos_v3 - world_pos_v1;
	Vec2D vec23 = world_pos_v3 - world_pos_v2;

	// составление векторо от каждой точки до центра окружности
	Vec2D vec10 = world_pos_circle - world_pos_v1;
	Vec2D vec20 = world_pos_circle - world_pos_v2;
	Vec2D vec30 = world_pos_circle - world_pos_v3;

	// Расстояние от точики O до каждой из сторон треугольника
	float h_12 = vec10.Length() * fabs(vec12.FindSin(vec10));
	float h_13 = vec10.Length() * fabs(vec13.FindSin(vec10));
	float h_23 = vec20.Length() * fabs(vec23.FindSin(vec20));

	// Координаты точки O, спроецированной на соответствующую сторону треугольника
	Vec2D p_12 = world_pos_v1 + vec12.Normalize() * vec10.Length() * vec12.FindCos(vec10);
	Vec2D p_13 = world_pos_v1 + vec13.Normalize() * vec10.Length() * vec13.FindCos(vec10);
	Vec2D p_23 = world_pos_v2 + vec23.Normalize() * vec20.Length() * vec23.FindCos(vec20);

	//Debug
	float a = (p_12 - world_pos_circle).Length();
	float b = (p_13 - world_pos_circle).Length();
	float c = (p_23 - world_pos_circle).Length();

	// Поиск стороны, до которой расстояние минимально (при учете, что точка лежит на отрезке или отходит 
	// от его краев не больше, чем на R)

	float min_h = inf; //минимальное расстояние до стороны
	Vec2D min_line = {0, 0}; //минимальная сторона
	Vec2D min_dist_to_center = {0, 0}; //минимальное расстояние до центра окружности
	

	float offset = (world_pos_v1 - p_12).Length(); //смещение окружности относительно края отрезка
	if ((world_pos_v2 - p_12).Length() < offset)
		offset = (world_pos_v2 - p_12).Length();

	if (h_12 < min_h &&  // расстояние меньше, чем уже найденное
		((fabs((p_12 - world_pos_v1).Length() + (p_12 - world_pos_v2).Length() - (vec12.Length())) < eps) || //точка лежит на стороне
			(vec10.Length() < Radius || vec20.Length() < Radius))) //или окружность может натолкнуться краешком на сторону
	{
		min_h = h_12;
		min_line = vec12;
		min_dist_to_center = vec10;
	}


	offset = (world_pos_v1 - p_13).Length(); //смещение окружности относительно края отрезка
	if ((world_pos_v3 - p_13).Length() < offset)
		offset = (world_pos_v3 - p_13).Length();

	if (h_13 < min_h &&
		((fabs((p_13 - world_pos_v1).Length() + (p_13 - world_pos_v3).Length() - (vec13.Length())) < eps) ||
		(vec10.Length() < Radius || vec30.Length() < Radius)))
	{
		min_h = h_13;
		min_line = vec13;
		min_dist_to_center = vec10;
	}

	offset = (world_pos_v2 - p_23).Length(); //смещение окружности относительно края отрезка
	if ((world_pos_v3 - p_23).Length() < offset)
		offset = (world_pos_v3 - p_23).Length();

	if (h_23 < min_h && 
		((fabs((p_23 - world_pos_v2).Length() + (p_23 - world_pos_v3).Length() - (vec23.Length())) < eps) ||
		(vec20.Length() < Radius || vec30.Length() < Radius)))
	{
		min_h = h_23;
		min_line = vec23;
		min_dist_to_center = vec20;
	}


	if (min_h != inf && min_h < Radius)
	{
		//Vec2D n = (min_line.Cross(min_line.Cross(min_dist_to_center))).Normalize();

		//float alpha_double = 2 * acos(min_line.Dot(n) / n.Length() / min_line.Length());

		//Vec2D new_velocity = {cos(alpha_double) * Velocity.X - sin(alpha_double) * Velocity.Y,
		//					  sin(alpha_double) * Velocity.X + cos(alpha_double) * Velocity.Y};
		Vec2D new_velocity = { 1, 1 };
		Velocity = new_velocity;
	}
}