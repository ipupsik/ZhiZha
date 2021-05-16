#include "Component.h"
#include "Entity.h"
#include "MaterialComponent.h"
#include "Components.h"
#include "MeshResource.h"

struct ActorComponent : public ComponentData<Actor>
{
	MeshResource* Mesh;
	MaterialComponent Material;
	TransformComponent Transform;
};
