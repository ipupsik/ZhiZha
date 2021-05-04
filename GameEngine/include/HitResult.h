#pragma once

struct HitResult {
  class Actor;

  bool DoesHit;
  struct {
    float x, y, z;
  } HitLocation;

  Actor *HitActor;
};