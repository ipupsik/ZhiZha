#include "Components/TransformComponent.h"
#include "Components/MaterialComponent.h"
#include "Components/RenderedComponent.h"
#include "Zhizha_InitSystem.h"
#include "Components/MeshComponent.h"
#include "Components/MeshCollider.h"
#include <random>
#include <ctime>
#include <Components/SpeedComponent.h>
#include <ComponentDrop.h>
#include "Components/LayerComponent.h"
#include "ObjectDrawable.h"

void Zhizha_InitSystem::OnInit()
{
	//Initialize Enityty
	for (int i = 0; i < 10; i++)
	{
		Entity& ball = _entities->CreateEntity();

		_entities->GetOrAddComponent<MeshComponent>(ball, [&](MeshComponent& c) {
			c.Mesh = _resources.GetOrAddResource<MeshResource>("Circle");
			});

		_entities->GetOrAddComponent<MaterialComponent>(ball, [&](MaterialComponent& c) {
			c.VertexShader = _resources.GetOrAddResource<VertexShaderResource>("Circle");
			c.FragmentShader = _resources.GetOrAddResource<FragmentShaderResource>("Circle");
			c.Textures.emplace_back(_resources.GetOrAddResource<TextureResource>("Circle_Albedo.png"));
			c.attributesCount = 2;
			});

		_entities->GetOrAddComponent<TransformComponent>(ball, [&](TransformComponent& c) {
			c.Location = { 0 + 0.05f * i, 0.1 };
			c.Scale = { 0.3, 0.3 };
			c.Angle = 0.0f;
			c.parent = nullptr;
			});

		//Setting balls components
		_entities->GetOrAddComponent<RenderedComponent>(ball, [&](RenderedComponent& c) {
			c.DrawableObj = new ObjectDrawable;
			ObjectDrawable* DrawObj = dynamic_cast<ObjectDrawable*>(c.DrawableObj);

			DrawObj->material = &_entities->GetOrAddComponent<MaterialComponent>(ball);
			DrawObj->mesh = &_entities->GetOrAddComponent<MeshComponent>(ball);
			DrawObj->transform = &_entities->GetOrAddComponent<TransformComponent>(ball);

			});

		_entities->GetOrAddComponent<LayerComponent>(ball, [](LayerComponent& c) {
			c.Index = Game;
			});

		_entities->GetOrAddComponent<ComponentDrop>(ball);
		_entities->GetOrAddComponent<SpeedComponent>(ball);
	}
}

Zhizha_InitSystem::Zhizha_InitSystem(ResourceManager& resources)
	: _resources(resources) { }
