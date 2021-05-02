#pragma onve

#include "Actor.h"
#include <vector>

class GlobalWorld {
 public:
  std::vector<Actor *> WorldActors;

  void InitActor(const char *MeshFilename, const char *MaterialFilename);

  void InitActor(Actor *NewActor);

  void BeginPlay();

  void Tick(float DeltaSeconds);

  ~GlobalWorld();
};