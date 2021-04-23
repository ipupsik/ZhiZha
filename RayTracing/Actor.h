#ifndef _H_ACTOR_

#define _H_ACTOR_

#include "obj3d.h"
#include "Material.h"

class Actor
{
public:
	Actor();

	void InitMesh(const char* filename);

	void BeginPlay();
	void Tick(float DeltaSeconds);
	void Draw();

	struct
	{
		double X, Y, Z;
	} Location, Rotation, Scale;

	void InitMaterialShader(const char* filename);

private:
	Obj3d* Mesh;
	Material* Mat;
};

#endif

