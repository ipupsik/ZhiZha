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
#include "GlobalRotation_Component.h"

void SmallSkull_InitSystem::OnInit()
{
	//Initialize Enityty
	_skull = &_entities->CreateEntity();

	_entities->GetOrAddComponent<MeshComponent>(*_skull, [&](MeshComponent& c) {
		c.Mesh = _resources.GetOrAddResource<MeshResource>("skull_small");
		});

	_entities->GetOrAddComponent<MaterialComponent>(*_skull, [&](MaterialComponent& c) {
		c.VertexShader = _resources.GetOrAddResource<VertexShaderResource>("Map");
		c.FragmentShader = _resources.GetOrAddResource<FragmentShaderResource>("Map");
		c.Textures.emplace_back(_resources.GetOrAddResource<TextureResource>("Skull_Small_Albedo.png"));
		c.attributesCount = 2;
		});

	_entities->GetOrAddComponent<TransformComponent>(*_skull, [&](TransformComponent& c) {
		c.Location = { 0.0, -.2 };
		c.Scale = { 0.07, 0.07 };
		c.Angle = 0.0f;
		c.parent = nullptr;
		});

	_entities->GetOrAddComponent<LayerComponent>(*_skull, [](LayerComponent& c) {
		c.Index = Game;
	});

	_entities->GetOrAddComponent<GlobalRotation_Component>(*_skull);
}

SmallSkull_InitSystem::SmallSkull_InitSystem(ResourceManager& resources)
	: _resources(resources) { }

void SmallSkull_InitSystem::OnSceneUnload(Scene scene) {
	_entities->DestroyEntity(*_skull);
}
