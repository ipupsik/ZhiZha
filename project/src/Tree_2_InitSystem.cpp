#include "Components/TransformComponent.h"
#include "Components/MaterialComponent.h"
#include "Components/RenderedComponent.h"
#include "Tree_2_InitSystem.h"
#include "Components/MeshComponent.h"
#include <random>
#include <ctime>
#include <Components/SpeedComponent.h>
#include <ComponentDrop.h>
#include <DefinesPhysics.h>
#include "Components/LayerComponent.h"
#include "ObjectDrawable.h"

void Tree_2_InitSystem::OnInit()
{
	//Initialize Enityty
	Entity& tree_2 = _entities->CreateEntity();

	_entities->GetOrAddComponent<MeshComponent>(tree_2, [&](MeshComponent& c) {
		c.Mesh = _resources.GetOrAddResource<MeshResource>("tree_2");
		});

	_entities->GetOrAddComponent<MaterialComponent>(tree_2, [&](MaterialComponent& c) {
		c.VertexShader = _resources.GetOrAddResource<VertexShaderResource>("Map");
		c.FragmentShader = _resources.GetOrAddResource<FragmentShaderResource>("Map");
		c.Textures.emplace_back(_resources.GetOrAddResource<TextureResource>("Tree_2_Albedo.png"));
		c.attributesCount = 2;
		});

	_entities->GetOrAddComponent<TransformComponent>(tree_2, [&](TransformComponent& c) {
		c.Location = { 0.0, -.2 };
		c.Scale = { 0.07, 0.07 };
		c.Angle = 0.0f;
		c.parent = nullptr;
		});

	//Setting balls components
	_entities->GetOrAddComponent<RenderedComponent>(tree_2, [&](RenderedComponent& c) {
		c.DrawableObj = new ObjectDrawable;
		ObjectDrawable* DrawObj = dynamic_cast<ObjectDrawable*>(c.DrawableObj);

		DrawObj->material = &_entities->GetOrAddComponent<MaterialComponent>(tree_2);
		DrawObj->mesh = &_entities->GetOrAddComponent<MeshComponent>(tree_2);
		DrawObj->transform = &_entities->GetOrAddComponent<TransformComponent>(tree_2);

		});

	_entities->GetOrAddComponent<LayerComponent>(tree_2, [](LayerComponent& c) {
		c.Index = Game;
	});
}

Tree_2_InitSystem::Tree_2_InitSystem(ResourceManager& resources)
	: _resources(resources) { }