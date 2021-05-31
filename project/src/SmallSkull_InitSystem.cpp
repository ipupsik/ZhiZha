#include "Components/TransformComponent.h"
#include "Components/MaterialComponent.h"
#include "Components/RenderedComponent.h"
#include "SmallSkull_InitSystem.h"
#include "Components/MeshComponent.h"
#include <random>
#include <ctime>
#include <Components/SpeedComponent.h>
#include <ComponentDrop.h>
#include <DefinesPhysics.h>
#include "Components/LayerComponent.h"
#include "ObjectDrawable.h"

void SmallSkull_InitSystem::OnInit()
{
	//Initialize Enityty
	Entity& skull = _entities->CreateEntity();

	_entities->GetOrAddComponent<MeshComponent>(skull, [&](MeshComponent& c) {
		c.Mesh = _resources.GetOrAddResource<MeshResource>("skull_small");
		});

	_entities->GetOrAddComponent<MaterialComponent>(skull, [&](MaterialComponent& c) {
		c.VertexShader = _resources.GetOrAddResource<VertexShaderResource>("Map");
		c.FragmentShader = _resources.GetOrAddResource<FragmentShaderResource>("Map");
		c.Textures.emplace_back(_resources.GetOrAddResource<TextureResource>("Skull_Small_Albedo.png"));
		c.attributesCount = 2;
		});

	_entities->GetOrAddComponent<TransformComponent>(skull, [&](TransformComponent& c) {
		c.Location = { 0.0, -.2 };
		c.Scale = { 0.07, 0.07 };
		c.Angle = 0.0f;
		c.parent = nullptr;
		});

	//Setting balls components
	_entities->GetOrAddComponent<RenderedComponent>(skull, [&](RenderedComponent& c) {
		c.DrawableObj = new ObjectDrawable;
		ObjectDrawable* DrawObj = dynamic_cast<ObjectDrawable*>(c.DrawableObj);

		DrawObj->material = &_entities->GetOrAddComponent<MaterialComponent>(skull);
		DrawObj->mesh = &_entities->GetOrAddComponent<MeshComponent>(skull);
		DrawObj->transform = &_entities->GetOrAddComponent<TransformComponent>(skull);

		});

	_entities->GetOrAddComponent<LayerComponent>(skull, [](LayerComponent& c) {
		c.Index = Game;
	});
}

SmallSkull_InitSystem::SmallSkull_InitSystem(ResourceManager& resources)
	: _resources(resources) { }
