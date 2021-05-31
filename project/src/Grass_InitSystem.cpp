#include "Components/TransformComponent.h"
#include "Components/MaterialComponent.h"
#include "Components/RenderedComponent.h"
#include "Grass_InitSystem.h"
#include "Components/MeshComponent.h"
#include <random>
#include <ctime>
#include <Components/SpeedComponent.h>
#include <ComponentDrop.h>
#include <DefinesPhysics.h>
#include "Components/LayerComponent.h"
#include "GlobalRotation_Component.h"

void Grass_InitSystem::OnInit()
{
	//Initialize Enityty
	Entity& grass = _entities->CreateEntity();

	_entities->GetOrAddComponent<MeshComponent>(grass, [&](MeshComponent& c) {
		c.Mesh = _resources.GetOrAddResource<MeshResource>("grass");
		});

	_entities->GetOrAddComponent<MaterialComponent>(grass, [&](MaterialComponent& c) {
		c.VertexShader = _resources.GetOrAddResource<VertexShaderResource>("Map");
		c.FragmentShader = _resources.GetOrAddResource<FragmentShaderResource>("Map");
		c.Textures.emplace_back(_resources.GetOrAddResource<TextureResource>("grass_Albedo.png"));
		c.attributesCount = 2;
		});

	_entities->GetOrAddComponent<TransformComponent>(grass, [&](TransformComponent& c) {
		c.Location = { 0.0, -.2 };
		c.Scale = { 0.07, 0.07 };
		c.Angle = 0.0f;
		c.parent = nullptr;
		});

	_entities->GetOrAddComponent<LayerComponent>(grass, [](LayerComponent& c) {
		c.Index = Game;
	});

	_entities->GetOrAddComponent<GlobalRotation_Component>(grass);
}

Grass_InitSystem::Grass_InitSystem(ResourceManager& resources)
	: _resources(resources) { }
