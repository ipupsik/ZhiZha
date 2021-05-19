#include "Systems/CreateComplexCollisionSystem.h"

#include "Components/ActorComponent.h"
#include "Components/ComplexCollisionComponent.h"
#include "SFML/System/Vector2.hpp"

void CreateComplexCollisionSystem::OnInit()
{
	auto Entities = _entities->GetEntitiesBy<ActorComponent, ComplexCollisionComponent>();

    for (auto& it : Entities)
    {
		auto [Actor, ComplexCollision] = it.Components;

		for (int i = 0; i < Actor->Mesh->_faces.size(); i++)
		{
			sf::Vector2f v1, v2, v3;
			v1.x = Actor->Mesh->_vertices[Actor->Mesh->_faces[i].v1].x;
			v1.y = Actor->Mesh->_vertices[Actor->Mesh->_faces[i].v1].y;

			v2.x = Actor->Mesh->_vertices[Actor->Mesh->_faces[i].v2].x;
			v2.y = Actor->Mesh->_vertices[Actor->Mesh->_faces[i].v2].y;

			v3.x = Actor->Mesh->_vertices[Actor->Mesh->_faces[i].v3].x;
			v3.y = Actor->Mesh->_vertices[Actor->Mesh->_faces[i].v3].y;

			ComplexCollision->Collision.push_back({ v1, v2, v3 });
		}
    }
}