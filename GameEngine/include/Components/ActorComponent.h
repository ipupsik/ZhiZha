#include "Component.h"
#include "Entity.h"
#include "MaterialComponent.h"
#include "Components.h"
#include "MeshResource.h"

struct ActorComponent : public ComponentData<ActorComponent>
{
	ActorComponent* parent;

	MeshResource* Mesh;
	MaterialComponent Material;
	TransformComponent Transform;
};
