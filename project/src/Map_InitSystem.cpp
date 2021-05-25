#include "Components/TransformComponent.h"
#include "Components/MaterialComponent.h"
#include "Components/RenderedComponent.h"
#include "Map_InitSystem.h"
#include "Components/MeshComponent.h"
#include "Components/MeshCollider.h"
#include <random>
#include <ctime>
#include <Components/SpeedComponent.h>
#include <ComponentDrop.h>
#include "Components/LayerComponent.h"
#include "ObjectDrawable.h"

void Map_InitSystem::OnInit()
{
	//Initialize Enityty
	Entity& map = _entities->CreateEntity();

	_entities->GetOrAddComponent<MeshComponent>(map, [&](MeshComponent& c) {
		c.Mesh = _resources.GetOrAddResource<MeshResource>("Map");
		});

	_entities->GetOrAddComponent<MaterialComponent>(map, [&](MaterialComponent& c) {
		c.VertexShader = _resources.GetOrAddResource<VertexShaderResource>("Map");
		c.FragmentShader = _resources.GetOrAddResource<FragmentShaderResource>("Map");
		c.Textures.emplace_back(_resources.GetOrAddResource<TextureResource>("Map_Albedo.png"));
		c.attributesCount = 2;
		});

	_entities->GetOrAddComponent<TransformComponent>(map, [&](TransformComponent& c) {
		c.Location = { 0, -0.2 };
		c.Scale = { 0.6, 0.6 };
		c.Angle = 0.0f;
		c.parent = nullptr;
		});

	//Setting balls components
	_entities->GetOrAddComponent<RenderedComponent>(map, [&](RenderedComponent& c) {
		c.DrawableObj = new ObjectDrawable;
		ObjectDrawable* DrawObj = dynamic_cast<ObjectDrawable*>(c.DrawableObj);

		DrawObj->material = &_entities->GetOrAddComponent<MaterialComponent>(map);
		DrawObj->mesh = &_entities->GetOrAddComponent<MeshComponent>(map);
		DrawObj->transform = &_entities->GetOrAddComponent<TransformComponent>(map);

		});

	_entities->GetOrAddComponent<LayerComponent>(map, [](LayerComponent& c) {
		c.Index = Game;
	});

	_entities->GetOrAddComponent<ComponentDrop>(map);
	_entities->GetOrAddComponent<SpeedComponent>(map);
}

Map_InitSystem::Map_InitSystem(ResourceManager& resources)
	: _resources(resources) { }
