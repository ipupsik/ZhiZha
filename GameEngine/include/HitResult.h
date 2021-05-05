#pragma once

#include "Actor.h"

struct HitResult {
  bool DoesHit;
  struct {
    float x, y, z;
  } HitLocation;

  Actor *HitActor;
};