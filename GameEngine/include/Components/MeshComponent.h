#pragma once

#include "Component.h"
#include "MeshResource.h"

struct MeshComponent : public ComponentData<MeshComponent>
{
	sf::VertexBuffer* Buffer;
	sf::Int64 Elements;
	sf::Int32 FacesSize;
};
