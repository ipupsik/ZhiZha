#include "Components/TransformComponent.h"
#include "Components/MaterialComponent.h"
#include "Components/RenderedComponent.h"
#include "BackGround_InitSystem.h"
#include "Components/MeshComponent.h"
#include <random>
#include <ctime>
#include <Components/SpeedComponent.h>
#include <ComponentDrop.h>
#include <DefinesPhysics.h>
#include "Components/LayerComponent.h"
#include "ObjectDrawable.h"

void BackGround_InitSystem::OnInit()
{
	//Initialize Enityty
	Entity& BackGround = _entities->CreateEntity();

	_entities->GetOrAddComponent<MeshComponent>(BackGround, [&](MeshComponent& c) {
		c.Mesh = _resources.GetOrAddResource<MeshResource>("BackGround");
		});

	_entities->GetOrAddComponent<MaterialComponent>(BackGround, [&](MaterialComponent& c) {
		c.VertexShader = _resources.GetOrAddResource<VertexShaderResource>("BackGround");
		c.FragmentShader = _resources.GetOrAddResource<FragmentShaderResource>("BackGround");
		c.Textures.emplace_back(_resources.GetOrAddResource<TextureResource>("lava.jpg"));
		c.attributesCount = 2;
		});

	_entities->GetOrAddComponent<TransformComponent>(BackGround, [&](TransformComponent& c) {
		c.Location = { 0.0, 0.0 };
		c.Scale = { 1, 1 };
		c.Angle = 0.0f;
		c.parent = nullptr;
		});

	//Setting balls components
	_entities->GetOrAddComponent<RenderedComponent>(BackGround, [&](RenderedComponent& c) {
		c.DrawableObj = new ObjectDrawable;
		ObjectDrawable* DrawObj = dynamic_cast<ObjectDrawable*>(c.DrawableObj);

		DrawObj->material = &_entities->GetOrAddComponent<MaterialComponent>(BackGround);
		DrawObj->mesh = &_entities->GetOrAddComponent<MeshComponent>(BackGround);
		DrawObj->transform = &_entities->GetOrAddComponent<TransformComponent>(BackGround);

		});

	_entities->GetOrAddComponent<LayerComponent>(BackGround, [](LayerComponent& c) {
		c.Index = Game;
	});
}

BackGround_InitSystem::BackGround_InitSystem(ResourceManager& resources)
	: _resources(resources) { }
