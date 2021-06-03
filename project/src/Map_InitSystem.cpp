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
	_map = &_entities->CreateEntity();

	_entities->GetOrAddComponent<MeshComponent>(*_map, [&](MeshComponent& c) {
		c.Mesh = _resources.GetOrAddResource<MeshResource>("Map");
		});

	_entities->GetOrAddComponent<MaterialComponent>(*_map, [&](MaterialComponent& c) {
		c.VertexShader = _resources.GetOrAddResource<VertexShaderResource>("Map");
		c.FragmentShader = _resources.GetOrAddResource<FragmentShaderResource>("Map");
		c.Textures.emplace_back(_resources.GetOrAddResource<TextureResource>("Map_Albedo.png"));
		c.attributesCount = 2;
		});

	_entities->GetOrAddComponent<TransformComponent>(*_map, [&](TransformComponent& c) {
		c.Location = { 0.0, -.2 };
		c.Scale = { 0.07, 0.07 };
		c.Angle = 0.0f;
		c.parent = nullptr;
		});

	_entities->GetOrAddComponent<LayerComponent>(*_map, [](LayerComponent& c) {
		c.Index = Game;
	});

	_entities->GetOrAddComponent<GlobalRotation_Component>(*_map);
	_entities->GetOrAddComponent<ComplexCollisionComponent>(*_map);
}

Map_InitSystem::Map_InitSystem(ResourceManager& resources)
	: _resources(resources) { }

void Map_InitSystem::OnSceneUnload(Scene scene) {
	_entities->DestroyEntity(*_map);
}
