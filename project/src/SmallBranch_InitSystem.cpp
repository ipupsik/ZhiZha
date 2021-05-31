#include "Components/TransformComponent.h"
#include "Components/MaterialComponent.h"
#include "Components/RenderedComponent.h"
#include "SmallBrunch_InitSystem.h"
#include "Components/MeshComponent.h"
#include <random>
#include <ctime>
#include <Components/SpeedComponent.h>
#include <ComponentDrop.h>
#include <DefinesPhysics.h>
#include "Components/LayerComponent.h"
#include "ObjectDrawable.h"

void SmallBrunch_InitSystem::OnInit()
{
	//Initialize Enityty
	Entity& brunch = _entities->CreateEntity();

	_entities->GetOrAddComponent<MeshComponent>(brunch, [&](MeshComponent& c) {
		c.Mesh = _resources.GetOrAddResource<MeshResource>("brunch_small");
		});

	_entities->GetOrAddComponent<MaterialComponent>(brunch, [&](MaterialComponent& c) {
		c.VertexShader = _resources.GetOrAddResource<VertexShaderResource>("Map");
		c.FragmentShader = _resources.GetOrAddResource<FragmentShaderResource>("Map");
		c.Textures.emplace_back(_resources.GetOrAddResource<TextureResource>("Small_Brunch_Albedo.png"));
		c.attributesCount = 2;
		});

	_entities->GetOrAddComponent<TransformComponent>(brunch, [&](TransformComponent& c) {
		c.Location = { 0.0, -.2 };
		c.Scale = { 0.07, 0.07 };
		c.Angle = 0.0f;
		c.parent = nullptr;
		});

	//Setting balls components
	_entities->GetOrAddComponent<RenderedComponent>(brunch, [&](RenderedComponent& c) {
		c.DrawableObj = new ObjectDrawable;
		ObjectDrawable* DrawObj = dynamic_cast<ObjectDrawable*>(c.DrawableObj);

		DrawObj->material = &_entities->GetOrAddComponent<MaterialComponent>(brunch);
		DrawObj->mesh = &_entities->GetOrAddComponent<MeshComponent>(brunch);
		DrawObj->transform = &_entities->GetOrAddComponent<TransformComponent>(brunch);

		});

	_entities->GetOrAddComponent<LayerComponent>(brunch, [](LayerComponent& c) {
		c.Index = Game;
	});
}

SmallBrunch_InitSystem::SmallBrunch_InitSystem(ResourceManager& resources)
	: _resources(resources) { }
