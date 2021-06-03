#include "Components/TransformComponent.h"
#include "Components/MaterialComponent.h"
#include "Components/RenderedComponent.h"
#include "Tree_1_InitSystem.h"
#include "Components/MeshComponent.h"
#include <random>
#include <ctime>
#include <Components/SpeedComponent.h>
#include <ComponentDrop.h>
#include <DefinesPhysics.h>
#include "Components/LayerComponent.h"
#include "GlobalRotation_Component.h"

void Tree_1_InitSystem::OnInit()
{
	//Initialize Enityty
	_tree = &_entities->CreateEntity();

	_entities->GetOrAddComponent<MeshComponent>(*_tree, [&](MeshComponent& c) {
		c.Mesh = _resources.GetOrAddResource<MeshResource>("tree_1");
		});

	_entities->GetOrAddComponent<MaterialComponent>(*_tree, [&](MaterialComponent& c) {
		c.VertexShader = _resources.GetOrAddResource<VertexShaderResource>("Map");
		c.FragmentShader = _resources.GetOrAddResource<FragmentShaderResource>("Map");
		c.Textures.emplace_back(_resources.GetOrAddResource<TextureResource>("Tree_3_Albedo.png"));
		c.attributesCount = 2;
		});

	_entities->GetOrAddComponent<TransformComponent>(*_tree, [&](TransformComponent& c) {
		c.Location = { 0.0, -.2 };
		c.Scale = { 0.07, 0.07 };
		c.Angle = 0.0f;
		c.parent = nullptr;
		});

	_entities->GetOrAddComponent<LayerComponent>(*_tree, [](LayerComponent& c) {
		c.Index = Game;
	});

	_entities->GetOrAddComponent<GlobalRotation_Component>(*_tree);
}

Tree_1_InitSystem::Tree_1_InitSystem(ResourceManager& resources)
	: _resources(resources) { }

void Tree_1_InitSystem::OnSceneUnload(Scene scene) {
	_entities->DestroyEntity(*_tree);
}
