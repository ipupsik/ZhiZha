#include "Collision.h"
#include <cmath>
#include "Actor.h"
#include "utils.h"

using namespace sf::Extensions::Vector2;

Collision::Collision() {}

Collision::Collision(std::weak_ptr<Actor> parent) {
	Parent = parent;
}

CollisionSphere::CollisionSphere(sf::Vector2f _Position, float _Radius, std::weak_ptr<Actor> parent)
	: Collision(parent) {
	ShapeType = CollisionShape::Sphere;

	Velocity = {0, 0};
	Acceleration = {0, 0};
	Position = _Position;
	Radius = _Radius;
}

CollisionTriangle::CollisionTriangle(sf::Vector2f _Position_v1,
                                     sf::Vector2f _Position_v2,
                                     sf::Vector2f _Position_v3,
                                     std::weak_ptr<Actor> parent) : Collision(parent) {
	ShapeType = CollisionShape::Triangle;

	v1 = _Position_v1;
	v2 = _Position_v2;
	v3 = _Position_v3;
}

void CollisionTriangle::CollisionDetection_SphereSphere(std::shared_ptr<Collision> OtherCollision,
                                                        HitResult& OutputHitResult) {}

void CollisionTriangle::CollisionDetection_SphereTriangle(std::shared_ptr<Collision> OtherCollision,
                                                          HitResult& OutputHitResult) {}

void CollisionTriangle::UpdatePhysicState(float DeltaSeconds) {}

void Collision::CollisionDetection(std::shared_ptr<Collision> OtherCollision,
                                   HitResult& OutputHitResult) {
	if (ShapeType == CollisionShape::Sphere) {
		if (OtherCollision->ShapeType == CollisionShape::Sphere) {
			CollisionDetection_SphereSphere(OtherCollision, OutputHitResult);
		}
		else if (OtherCollision->ShapeType == CollisionShape::Triangle) {
			CollisionDetection_SphereTriangle(OtherCollision, OutputHitResult);
		}
	}
}

void CollisionSphere::UpdatePhysicState(float DeltaSeconds) {
	Position.x += Velocity.x + Acceleration.x * DeltaSeconds * DeltaSeconds / 2;
	Position.y += Velocity.y + Acceleration.y * DeltaSeconds * DeltaSeconds / 2;

	Velocity.x += Acceleration.x * DeltaSeconds;
	Velocity.y += Acceleration.y * DeltaSeconds;
}

void CollisionSphere::CollisionDetection_SphereSphere(std::shared_ptr<Collision> OtherCollision,
                                                      HitResult& OutputHitResult) {
	auto Other = dynamic_cast<CollisionSphere*>(OtherCollision.get());

	float Dist = sqrt(
		(Position.x - Other->Position.x) * (Position.x - Other->Position.x) + (Position.y - Other->Position.y) * (
			Position.y - Other->Position.y));
	if (Dist <= Radius + Other->Radius) {
		float Scalar = (Velocity.x - Other->Velocity.x) * (Position.x - Other->Position.x) + (Velocity.y - Other->
			Velocity.y) * (Position.y - Other->Position.y);
		float Koeff = 2.0f * Other->Mas / (Mas + Other->Mas) * Scalar / (Dist * Dist);
		float newV1_x = Velocity.x - Koeff * (Position.x - Other->Position.x);
		float newV1_y = Velocity.y - Koeff * (Position.y - Other->Position.y);

		Scalar = (Other->Velocity.x - Velocity.x) * (Other->Position.x - Position.x) + (Other->Velocity.y - Velocity.y)
			* (Other->Position.y - Position.y);
		Koeff = 2.0f * Mas / (Mas + Other->Mas) * Scalar / (Dist * Dist);
		float newV2_x = Other->Velocity.x - Koeff * (Other->Position.x - Position.x);
		float newV2_y = Other->Velocity.y - Koeff * (Other->Position.y - Position.y);

		Velocity.x = newV1_x;
		Velocity.y = newV1_y;

		Other->Velocity.x = newV2_x;
		Other->Velocity.y = newV2_y;
	}
}

sf::Vector2f find_parent_position(std::shared_ptr<Collision> Collision) {
	auto parent = Collision->Parent.lock();
	sf::Vector2f pos = {0, 0};

	while (parent) {
		pos += parent->Transform()->Location;

		parent = std::make_shared<Actor>(*parent->GetParent());
	}

	return {pos.x, pos.y};
}

void CollisionSphere::CollisionDetection_SphereTriangle(std::shared_ptr<Collision> otherCollision,
                                                        HitResult& outputHitResult) {
	const auto otherTriangle = std::dynamic_pointer_cast<CollisionTriangle>(otherCollision);

	const float eps = 0.000001f;
	const float inf = 50000;

	const sf::Vector2f posParentTriangle = find_parent_position(otherTriangle);
	const sf::Vector2f posParentMy = find_parent_position(shared_from_this());

	const sf::Vector2f worldPosV1 = otherTriangle->v1 + posParentTriangle;
	const sf::Vector2f worldPosV2 = otherTriangle->v2 + posParentTriangle;
	const sf::Vector2f worldPosV3 = otherTriangle->v3 + posParentTriangle;
	const sf::Vector2f worldPosCircle = Position + posParentMy;

	sf::Vector2f vec12 = worldPosV2 - worldPosV1;
	sf::Vector2f vec13 = worldPosV3 - worldPosV1;
	sf::Vector2f vec23 = worldPosV3 - worldPosV2;

	const sf::Vector2f vec10 = worldPosCircle - worldPosV1;
	const sf::Vector2f vec20 = worldPosCircle - worldPosV2;
	const sf::Vector2f vec30 = worldPosCircle - worldPosV3;

	const float h12 = vec10->*Length<float>() * fabs(vec12->*Sin(vec10));
	const float h13 = vec10->*Length<float>() * fabs(vec13->*Sin(vec10));
	const float h23 = vec20->*Length<float>() * fabs(vec23->*Sin(vec20));

	const sf::Vector2f p12 = worldPosV1 + vec10->*Normalize<float>() * vec10->*Length<float>() * vec12->*Cos(vec10);
	const sf::Vector2f p13 = worldPosV1 + vec13->*Normalize<float>() * vec10->*Length<float>() * vec13->*Cos(vec10);
	const sf::Vector2f p23 = worldPosV2 + vec23->*Normalize<float>() * vec20->*Length<float>() * vec23->*Cos(vec20);

	float a = p12->*Magnitude(worldPosCircle);
	float b = p13->*Magnitude(worldPosCircle);
	float c = p23->*Magnitude(worldPosCircle);

	float min_h = inf;
	sf::Vector2f min_line = {0, 0};
	sf::Vector2f min_dist_to_center = {0, 0};


	float offset = worldPosV1->*Magnitude(p12);
	if (worldPosV2->*Magnitude(p12) < offset)
		offset = worldPosV2->*Magnitude(p12);

	if (h12 < min_h
		&& (fabs(worldPosV1->*Magnitude(p12) + worldPosV2->*Magnitude(p12) - vec12->*Length<float>()) < eps
			|| (vec10->*Length<float>() < Radius || vec20->*Length<float>() < Radius))) {
		min_h = h12;
		min_line = vec12;
		min_dist_to_center = vec10;
	}

	offset = worldPosV1->*Magnitude(p13);
	if (worldPosV3->*Magnitude(p13) < offset)
		offset = worldPosV3->*Magnitude(p13);

	if (h13 < min_h &&
		(fabs(worldPosV1->*Magnitude(p13) + worldPosV3->*Magnitude(p13) - (vec13->*Length<float>())) < eps || (
			vec10->*Length<float>() < Radius || vec30->*Length<float>() < Radius))) {
		min_h = h13;
		min_line = vec13;
		min_dist_to_center = vec10;

		//does_hit = true;
	}
	/*float cos_012 = vec12.Dot(vec10) / vec12.Length<float>() / vec10.Length<float>();
	float cos_021 = (vec12 * -1).Dot(vec20) / vec12.Length<float>() / vec20.Length<float>();

	float cos_013 = vec13.Dot(vec10) / vec13.Length<float>() / vec10.Length<float>();
	float cos_031 = (vec13 * -1).Dot(vec30) / vec13.Length<float>() / vec30.Length<float>();

	float cos_023 = vec23.Dot(vec20) / vec23.Length<float>() / vec20.Length<float>();
	float cos_032 = (vec23 * -1).Dot(vec30) / vec23.Length<float>() / vec30.Length<float>();

	float h_12 = fabs(sqrt(pow(vec10.Length<float>(), 2) - pow(cos_012 * vec10.Length<float>(),2)));
	float h_13 = fabs(sqrt(pow(vec10.Length<float>(), 2) - pow(cos_013 * vec10.Length<float>(),2)));
	float h_23 = fabs(sqrt(pow(vec20.Length<float>(), 2) - pow(cos_023 * vec20.Length<float>(),2))); ��� �������*/

	/*(bool does_hit = false;

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
	} */

	offset = worldPosV2->*Magnitude(p23);
	if (worldPosV3->*Magnitude(p23) < offset)
		offset = worldPosV3->*Magnitude(p23);

	if (h23 < min_h && ((fabs(
		worldPosV2->*Magnitude(p23) + worldPosV3->*Magnitude(p23) - (vec23->*Length<float>())) < eps) || (vec20->*
		Length<float>() < Radius || vec30->*Length<float>() < Radius)))

		//if (cos_023 >= 0 && cos_032 >= 0)
	{
		//if (!does_hit || h_23 < min_h)
		min_h = h23;
		min_line = vec23;
		min_dist_to_center = vec20;

		//does_hit = true;
	}
	/*if (does_hit && min_h < Radius) ��� �������
	{
	    Vec2D n = (min_line.Cross(min_line.Cross(min_dist_to_center))).Normalize();*/

	if (min_h != inf && min_h < Radius) {
		//Vec2D n = (min_line.Cross(min_line.Cross(min_dist_to_center))).Normalize();

		//float alpha_double = 2 * acos(min_line.Dot(n) / n.Length<float>() / min_line.Length<float>());

		/*//Vec2D new_velocity = {cos(alpha_double) * Velocity.X - sin(alpha_double) * Velocity.Y,
		//					  sin(alpha_double) * Velocity.X + cos(alpha_double) * Velocity.Y};
		Vec2D new_velocity = { 1, 1 };
		Velocity = new_velocity; ��� ������ */

		//Velocity = new_velocity;
		Velocity = {0, 0};
	}
}
