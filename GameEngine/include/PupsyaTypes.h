#pragma once

struct Vec2D {
  float X, Y;

  static Vec2D FindNormal(Vec2D other);

  Vec2D operator*(float value) const;

  Vec2D operator/(float value) const;

  Vec2D operator*(Vec2D other) const;

  Vec2D operator-(Vec2D other) const;

  Vec2D operator+(Vec2D other) const;

  [[nodiscard]] float Dot(Vec2D other) const;

  [[nodiscard]] float FindCos(Vec2D other) const;

  [[nodiscard]] float Cross(Vec2D other) const;

  [[nodiscard]] float FindSin(Vec2D other) const;

  [[nodiscard]] float DistanceTo(Vec2D other) const;

  [[nodiscard]] float Length() const;

  [[nodiscard]] Vec2D Normalize() const;
};
