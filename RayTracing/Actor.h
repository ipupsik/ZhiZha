#pragma once

#include "StaticMesh.h"
#include "Material.h"
#include "Collision.h"
#include <vector>

class Collision;

class Actor
{
public:
	Actor();

	void InitMesh(const char* filename);
	void InitMesh(StaticMesh* Other);

	void BeginPlay();
	void Tick(float DeltaSeconds);
	void Draw();

	void MakeComplexCollision();

	struct
	{
		double X, Y, Z;
	} Location, Rotation, Scale;

	void InitMaterialShader(const char* filename);

private:
	StaticMesh* Mesh;
	Material* Mat;
	std::vector<Collision*> *Collider;
};

