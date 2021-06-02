#include "Systems/CameraMovingSystem.h"
#include <Components/TransformComponent.h>
#include "../PhysicsEngine/include/ComponentDrop.h"
#include "Systems/ComplexCollision_InitSystem.h"

#include "Components/ComplexCollisionComponent.h"
#include "Components/MeshComponent.h"

void ComplexCollision_InitSystem::OnInit() {
	const auto& items = _entities->GetEntitiesBy<MeshComponent, ComplexCollisionComponent>();

	for (auto& [_comps, _entity] : items)
	{
        auto& [_Mesh, CCC] = _comps;
        for (int i = 0; i < _Mesh->Mesh->_faces.size(); i++)
        {
            sf::Vector2f v1, v2, v3;
            v1.x = _Mesh->Mesh->_vertices[_Mesh->Mesh->_faces[i].x].x;
            v1.y = _Mesh->Mesh->_vertices[_Mesh->Mesh->_faces[i].x].y;
                

            v2.x = _Mesh->Mesh->_vertices[_Mesh->Mesh->_faces[i].y].x;
            v2.y = _Mesh->Mesh->_vertices[_Mesh->Mesh->_faces[i].y].y;

            v3.x = _Mesh->Mesh->_vertices[_Mesh->Mesh->_faces[i].z].x;
            v3.y = _Mesh->Mesh->_vertices[_Mesh->Mesh->_faces[i].z].y;

            CCC->ComplexCollision.push_back({ v1, v2, v3 });
        }
	}
}