#pragma once

#include "Entity.h"

struct HitResult {
  bool DoesHit;
  struct {
    float x, y, z;
  } HitLocation;

  Entity *HitActor;
};