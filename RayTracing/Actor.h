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
	~Actor();

	void InitMesh(const char* filename);
	void InitMesh(StaticMesh* Other);

	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds);
	virtual void Draw();

	void MakeComplexCollision();

	Vec2D Location, Rotation, Scale;

	void InitMaterialShader(const char* filename);

public:
	StaticMesh* Mesh;
	Material* Mat;
	std::vector<Collision*> *Collider;

	Actor* Parent;
};

