#ifndef _H_PUPSYATYPES_
#define _H_PUPSYATYPES_

struct Vec2D
{
	float X, Y;

	Vec2D operator*(float Value);
	Vec2D operator/(float Value);
	Vec2D operator*(Vec2D Other);
	Vec2D operator-(Vec2D Other);

	float Dot(Vec2D Other);

	float DistanceTo(Vec2D Other);
	float Length();
	Vec2D Normalize();
};

#endif
