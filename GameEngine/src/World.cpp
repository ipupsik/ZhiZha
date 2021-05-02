#include "World.h"

void GlobalWorld::InitActor(const char* MeshFilename, const char* MaterialFilename)
{
	Actor* NewActor = new Actor;
	NewActor->InitMesh(MeshFilename);
	NewActor->InitMaterialShader(MaterialFilename);

	WorldActors.push_back(NewActor);
}

void GlobalWorld::InitActor(Actor *NewActor)
{
	WorldActors.push_back(NewActor);
}

void GlobalWorld::BeginPlay()
{

	for (auto& it : WorldActors)
	{
		it->BeginPlay();
	}
}

void GlobalWorld::Tick(float DeltaSeconds)
{
	for (auto& it : WorldActors)
	{
		it->Tick(DeltaSeconds);
	}
}

GlobalWorld::~GlobalWorld()
{
	for (auto& it : WorldActors)
	{
		delete it;
	}
}