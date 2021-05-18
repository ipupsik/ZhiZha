#include "CreateComplexCollisionSystem.h"

#include "ActorComponent.h"
#include "Components.h"

void CreateComplexCollisionSystem::OnInit()
{
	auto Entities = _entities.GetEntitiesBy<ActorComponent, ComplexCollisionComponent>();

    for (auto& it : Entities)
    {
		auto [Actor, Collision] = it.Components;
		Collider = std::vector<Collision*>(0);

		for (int i = 0; i < Mesh->faces.size(); i++)
		{
			Vec2D v1, v2, v3;
			v1.X = Actor->Mesh->vertices[Mesh->faces[i].v1].X;
			v1.Y = Mesh->vertices[Mesh->faces[i].v1].Y;


			v2.X = Mesh->vertices[Mesh->faces[i].v2].X;
			v2.Y = Mesh->vertices[Mesh->faces[i].v2].Y;

			v3.X = Mesh->vertices[Mesh->faces[i].v3].X;
			v3.Y = Mesh->vertices[Mesh->faces[i].v3].Y;

			Collider.push_back(new CollisionTriangle(v1, v2, v3, this));
		}
    }
}