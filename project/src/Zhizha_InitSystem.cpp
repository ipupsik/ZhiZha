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
	for (int i = 0; i < 100; i++)
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
			c.Location = {
			((rand() % 1000) + (rand() % 100) / 100.0f) * 0.0001f,
			((rand() % 1000) + (rand() % 100) / 100.0f) * 0.0001f
			};
			c.Scale = { 0.1f, 0.1f } ;
			c.Angle = 0;
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

	//Initialize Enityty
	/*for (int i = 0; i < 10; i++)
	{
		auto& copy = _entities->Instantiate(ball);
		auto& transform = _entities->GetOrAddComponent<TransformComponent>(copy);

		transform.Location = {
			((rand() % 1000) + (rand() % 100) / 100.0f) * 0.001f,
			((rand() % 1000) + (rand() % 100) / 100.0f) * 0.001f
		};
		transform.Scale = { 5, 5 };
		transform.Angle = 0;
		transform.parent = nullptr;
	}*/
}

Zhizha_InitSystem::Zhizha_InitSystem(ResourceManager& resources)
	: _resources(resources) { }
