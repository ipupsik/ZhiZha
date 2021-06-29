#include "Components/TransformComponent.h"
#include "Components/MaterialComponent.h"
#include "Components/RenderedComponent.h"
#include "Map_InitSystem.h"
#include "Components/MeshComponent.h"
#include <random>
#include <ctime>
#include <Components/SpeedComponent.h>
#include <ComponentDrop.h>
#include <DefinesPhysics.h>
#include "Components/LayerComponent.h"
#include "GlobalRotation_Component.h"
#include "Components/ComplexCollisionComponent.h"

void Map_InitSystem::OnInit()
{
	//Initialize Enityty
	for (int i = 0; i < 4; i++)
	{
		Entity& map = _entities->CreateEntity();

		_entities->GetOrAddComponent<MeshComponent>(map, [&](MeshComponent& c) {
			c.Mesh = _resources.GetOrAddResource<MeshResource>("Map");
			});

		_entities->GetOrAddComponent<MaterialComponent>(map, [&](MaterialComponent& c) {
			c.VertexShader = _resources.GetOrAddResource<VertexShaderResource>("Map");
			c.FragmentShader = _resources.GetOrAddResource<FragmentShaderResource>("Map");
			std::string filename = "Map";
			filename += (char)('0' + i);
			filename += "_Albedo.png";
			c.Textures.emplace_back(_resources.GetOrAddResource<TextureResource>(filename));
			c.attributesCount = 2;
			});

		_entities->GetOrAddComponent<MyTransformComponent>(map, [&](MyTransformComponent& c) {
			c.Location = { -.3f * i + 0.3f, -1.0f , 0.f };
			c.Scale = { 0.14f, 0.14f, 0.14f };
			c.Angle = 0.0f;
			c.parent = nullptr;
			});

		_entities->GetOrAddComponent<LayerComponent>(map, [](LayerComponent& c) {
			c.Index = Game;
			});

		_entities->GetOrAddComponent<GlobalRotation_Component>(map);
		_entities->GetOrAddComponent<ComplexCollisionComponent>(map);
	}
}

Map_InitSystem::Map_InitSystem(ResourceManager& resources)
	: _resources(resources) { }
