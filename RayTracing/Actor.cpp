#include "Actor.h"

#include <glad/glad.h>

Actor::Actor() : Mesh(nullptr)
{

}

void Actor::InitMesh(const char* filename)
{
	Mesh = new StaticMesh;

	Mesh->ReadFile(filename);
	Mesh->Init();
}

void Actor::InitMesh(StaticMesh* Other)
{
	Mesh = Other;
}

void Actor::Tick(float DeltaSeconds)
{
	Draw();
}

void Actor::InitMaterialShader(const char* filename)
{
	Mat = new Material;

	Mat->InitShaders(filename);
}

void Actor::Draw()
{
	Mat->SetProgram();
	Mesh->Draw();
	Mat->ResetProgram();
}