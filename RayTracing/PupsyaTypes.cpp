#include "PupsyaTypes.h"
#include <cmath>

Vec2D Vec2D::operator*(float Value)
{
    return { X * Value, Y * Value };
}

Vec2D Vec2D::operator/(float Value)
{
    return { X / Value, Y / Value };
}

Vec2D Vec2D::operator*(Vec2D Other)
{
    return { X * Other.X, Y * Other.Y };
}

Vec2D Vec2D::operator-(Vec2D Other)
{
    return { X - Other.X, Y - Other.Y };
}

float Vec2D::Dot(Vec2D Other)
{
    return X * Other.X + Y * Other.Y;
}

float Vec2D::DistanceTo(Vec2D Other)
{
    return sqrt((X - Other.X) * (X - Other.X) + (Y - Other.Y) * (Y - Other.Y));
}

float Vec2D::Length()
{
    return sqrt(X * X + Y * Y);
}

Vec2D Vec2D::Normalize()
{
    float TmpLength = Length();
    return Vec2D({ X / TmpLength, Y / TmpLength });
}
