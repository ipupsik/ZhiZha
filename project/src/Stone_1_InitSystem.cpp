#include "Components/TransformComponent.h"
#include "Components/MaterialComponent.h"
#include "Components/RenderedComponent.h"
#include "Stone_1_InitSystem.h"
#include "Components/MeshComponent.h"
#include <random>
#include <ctime>
#include <Components/SpeedComponent.h>
#include <ComponentDrop.h>
#include <DefinesPhysics.h>
#include "Components/LayerComponent.h"
#include "GlobalRotation_Component.h"

void Stone_1_InitSystem::OnInit()
{
	//Initialize Enityty
	Entity& stone_1 = _entities->CreateEntity();

	_entities->GetOrAddComponent<MeshComponent>(stone_1, [&](MeshComponent& c) {
		c.Mesh = _resources.GetOrAddResource<MeshResource>("stone_1");
		});

	_entities->GetOrAddComponent<MaterialComponent>(stone_1, [&](MaterialComponent& c) {
		c.VertexShader = _resources.GetOrAddResource<VertexShaderResource>("Map");
		c.FragmentShader = _resources.GetOrAddResource<FragmentShaderResource>("Map");
		c.Textures.emplace_back(_resources.GetOrAddResource<TextureResource>("Stone_1_Albedo.png"));
		c.attributesCount = 2;
		});

	_entities->GetOrAddComponent<TransformComponent>(stone_1, [&](TransformComponent& c) {
		c.Location = { 0.0, -.2 };
		c.Scale = { 0.07, 0.07 };
		c.Angle = 0.0f;
		c.parent = nullptr;
		});

	_entities->GetOrAddComponent<LayerComponent>(stone_1, [](LayerComponent& c) {
		c.Index = Game;
	});

	_entities->GetOrAddComponent<GlobalRotation_Component>(stone_1);
}

Stone_1_InitSystem::Stone_1_InitSystem(ResourceManager& resources)
	: _resources(resources) { }
