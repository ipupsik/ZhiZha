#include "PupsyaTypes.h"
#include <cmath>

Vec2D Vec2D::operator*(float value) const {
    return {X * value, Y * value};
}

Vec2D Vec2D::operator/(float value) const {
    return {X / value, Y / value};
}

Vec2D Vec2D::operator*(Vec2D other) const {
    return {X * other.X, Y * other.Y};
}

Vec2D Vec2D::operator-(Vec2D other) const {
    return {X - other.X, Y - other.Y};
}

Vec2D Vec2D::operator+(Vec2D other) const {
    return {X + other.X, Y + other.Y};
}

float Vec2D::Dot(Vec2D other) const {
    return X * other.X + Y * other.Y;
}

float Vec2D::FindCos(Vec2D other) const {
    return Dot(other) / Length() / other.Length();
}

float Vec2D::Cross(Vec2D other) const {
    return X * other.Y - Y * other.X;
}

float Vec2D::FindSin(Vec2D other) const {
    return Cross(other) / Length() / other.Length();
}

Vec2D Vec2D::FindNormal(Vec2D other) {
    return Vec2D{other.Y, -1 * other.X};
}

float Vec2D::DistanceTo(Vec2D other) const {
    return std::sqrt((X - other.X) * (X - other.X) + (Y - other.Y) * (Y - other.Y));
}

float Vec2D::Length() const {
    return DistanceTo({0, 0});
}

Vec2D Vec2D::Normalize() const {
    auto TmpLength = Length();
    return {X / TmpLength, Y / TmpLength};
}
