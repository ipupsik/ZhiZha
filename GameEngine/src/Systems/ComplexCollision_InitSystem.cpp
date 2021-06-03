#include "Systems/CameraMovingSystem.h"
#include <Components/TransformComponent.h>
#include "../PhysicsEngine/include/ComponentDrop.h"
#include "Systems/ComplexCollision_InitSystem.h"

#include "Components/ComplexCollisionComponent.h"
#include "Components/MeshComponent.h"

void ComplexCollision_InitSystem::OnInit() {
    const auto& items = _entities->GetEntitiesBy<MeshComponent, ComplexCollisionComponent, TransformComponent>();

    for (auto& [_comps, _entity] : items)
    {
        auto& [_Mesh, CCC, transform] = _comps;
        for (int i = 0; i < _Mesh->Mesh->_faces.size(); i++)
        {
            sf::Vector2f v1, v2, v3;
            v1.x = _Mesh->Mesh->_vertices[_Mesh->Mesh->_faces[i].x].x * transform->Scale.x + transform->Location.x;
            v1.y = _Mesh->Mesh->_vertices[_Mesh->Mesh->_faces[i].x].y * transform->Scale.y + transform->Location.y;


            v2.x = _Mesh->Mesh->_vertices[_Mesh->Mesh->_faces[i].y].x * transform->Scale.x + transform->Location.x;
            v2.y = _Mesh->Mesh->_vertices[_Mesh->Mesh->_faces[i].y].y * transform->Scale.y + transform->Location.y;

            v3.x = _Mesh->Mesh->_vertices[_Mesh->Mesh->_faces[i].z].x * transform->Scale.x + transform->Location.x;
            v3.y = _Mesh->Mesh->_vertices[_Mesh->Mesh->_faces[i].z].y * transform->Scale.y + transform->Location.y;

            CCC->ComplexCollision.push_back({ v1, v2, v3 });
        }
    }
}