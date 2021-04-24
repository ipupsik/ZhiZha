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

void Actor::MakeComplexCollision()
{
	Collider = new std::vector<Collision*>(0);

	for (int i = 0; i < Mesh->faces.size(); i++)
	{
		Vec2D v1, v2, v3;
		v1.X = Mesh->vertices[Mesh->faces[i].v1].X;
		v1.Y = Mesh->vertices[Mesh->faces[i].v1].Y;

		v2.X = Mesh->vertices[Mesh->faces[i].v2].X;
		v2.Y = Mesh->vertices[Mesh->faces[i].v2].Y;

		v3.X = Mesh->vertices[Mesh->faces[i].v3].X;
		v3.Y = Mesh->vertices[Mesh->faces[i].v3].Y;

		Collider->push_back(new CollisionTriangle(v1, v2, v3));
	}
}