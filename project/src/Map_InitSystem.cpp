#include "Components/TransformComponent.h"
#include "Components/MaterialComponent.h"
#include "Map_InitSystem.h"
#include "Components/MeshComponent.h"
#include "Components/MeshCollider.h"
#include <random>
#include <ctime>
#include <Components/SpeedComponent.h>
#include <ComponentDrop.h>
#include "Components/LayerComponent.h"

void Map_InitSystem::OnInit()
{
	//Initialize Enityty
	Entity& map = _entities->CreateEntity();

	//Setting balls components
	_entities->GetOrAddComponent<MeshComponent>(map, [&](MeshComponent& c) {
		auto circle = _resources.GetOrAddResource<MeshResource>("Map");
	});

	_entities->GetOrAddComponent<LayerComponent>(map, [](LayerComponent& c) {
		c.Index = Game;
	});

	_entities->GetOrAddComponent<ComponentDrop>(map);
	_entities->GetOrAddComponent<SpeedComponent>(map);

	_entities->GetOrAddComponent<TransformComponent>(map, [](TransformComponent& c) {
		c.Location = {0, 400};
		c.Scale = { 1, 1 };
	});

	_entities->GetOrAddComponent<MaterialComponent>(map, [](MaterialComponent& c) {
		c.VertexShader = new VertexShaderResource("Map");
		c.FragmentShader = new FragmentShaderResource("Map");
		c.Textures.emplace_back(new TextureResource("Map_Albedo.png"));
		c.attributesCount = 2;
	});
}

Map_InitSystem::Map_InitSystem(ResourceManager& resources)
	: _resources(resources) { }
