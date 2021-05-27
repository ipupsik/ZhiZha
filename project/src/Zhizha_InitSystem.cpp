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
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
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
				i * 0.01f,
				j * 0.01f
				};
				c.Scale = { 0.1f, 0.1f };
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
	}
}

Zhizha_InitSystem::Zhizha_InitSystem(ResourceManager& resources)
	: _resources(resources) { }
