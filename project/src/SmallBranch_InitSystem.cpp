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
#include "GlobalRotation_Component.h"

void SmallBrunch_InitSystem::OnInit()
{
	//Initialize Enityty
	_brunch = &_entities->CreateEntity();

	_entities->GetOrAddComponent<MeshComponent>(*_brunch, [&](MeshComponent& c) {
		c.Mesh = _resources.GetOrAddResource<MeshResource>("brunch_small");
		});

	_entities->GetOrAddComponent<MaterialComponent>(*_brunch, [&](MaterialComponent& c) {
		c.VertexShader = _resources.GetOrAddResource<VertexShaderResource>("Map");
		c.FragmentShader = _resources.GetOrAddResource<FragmentShaderResource>("Map");
		c.Textures.emplace_back(_resources.GetOrAddResource<TextureResource>("Small_Brunch_Albedo.png"));
		c.attributesCount = 2;
		});

	_entities->GetOrAddComponent<TransformComponent>(*_brunch, [&](TransformComponent& c) {
		c.Location = { 0.0, -.2 };
		c.Scale = { 0.07, 0.07 };
		c.Angle = 0.0f;
		c.parent = nullptr;
		});

	_entities->GetOrAddComponent<LayerComponent>(*_brunch, [](LayerComponent& c) {
		c.Index = Game;
	});

	_entities->GetOrAddComponent<GlobalRotation_Component>(*_brunch);
}

SmallBrunch_InitSystem::SmallBrunch_InitSystem(ResourceManager& resources)
	: _resources(resources) { }

void SmallBrunch_InitSystem::OnSceneUnload(Scene scene) {
	_entities->DestroyEntity(*_brunch);
}
