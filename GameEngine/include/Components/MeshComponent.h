#pragma once

#include "Component.h"
#include "MeshResource.h"

struct MeshComponent : public ComponentData<MeshComponent>
{
	MeshResource* Mesh;
};
