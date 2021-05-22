#include "Systems/CreateComplexCollisionSystem.h"

#include "Components/MeshComponent.h"
#include "Components/ComplexCollisionComponent.h"
#include "SFML/System/Vector2.hpp"
#include "Components/TransformComponent.h"
#include "Components/MaterialComponent.h"

void CreateComplexCollisionSystem::OnInit()
{
	auto Entities = _entities->GetEntitiesBy<MeshComponent, ComplexCollisionComponent>();

    for (auto& it : Entities)
    {
		auto [mesh, complexCollision] = it.Components;

		//FIXME
//		for (const auto& face: mesh->Mesh->_faces)
//		{
//			sf::Vector2f v1, v2, v3;
//			v1.x = mesh->Mesh->_vertices[face.v1].x;
//			v1.y = mesh->Mesh->_vertices[face.v1].y;
//
//			v2.x = mesh->Mesh->_vertices[face.v2].x;
//			v2.y = mesh->Mesh->_vertices[face.v2].y;
//
//			v3.x = mesh->Mesh->_vertices[face.v3].x;
//			v3.y = mesh->Mesh->_vertices[face.v3].y;
//
//			complexCollision->Collision.push_back({ v1, v2, v3 });
//		}
    }
}