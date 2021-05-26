#include "Components/TransformComponent.h"
#include "Components/MaterialComponent.h"
#include "Components/RenderedComponent.h"
#include "ZhizhaVolume_InitSystem.h"
#include "Components/MeshComponent.h"
#include "Components/MeshCollider.h"
#include <random>
#include <ctime>
#include <Components/SpeedComponent.h>
#include <ComponentDrop.h>
#include "Components/LayerComponent.h"
#include "ZhizhaVolumeComponent.h"
#include "DrawableZhizha.h"

void ZhizhaVolume_InitSystem::OnInit()
{
	Entity& ZhizhaVolume = _entities->CreateEntity();

	_entities->GetOrAddComponent<MaterialComponent>(ZhizhaVolume, [&](MaterialComponent& c) {
		c.VertexShader = _resources.GetOrAddResource<VertexShaderResource>("Circle");
		c.FragmentShader = _resources.GetOrAddResource<FragmentShaderResource>("Circle");
		c.Textures.emplace_back(_resources.GetOrAddResource<TextureResource>("Circle_Albedo.png"));
		c.attributesCount = 2;
		});

	//Setting balls components
	_entities->GetOrAddComponent<RenderedComponent>(ZhizhaVolume, [&](RenderedComponent& c) {
		c.DrawableObj = new DrawableZhizha;
		DrawableZhizha* DrawObj = dynamic_cast<DrawableZhizha*>(c.DrawableObj);

		DrawObj->material = &_entities->GetOrAddComponent<MaterialComponent>(ZhizhaVolume);
		});

	_entities->GetOrAddComponent<LayerComponent>(ZhizhaVolume, [](LayerComponent& c) {
		c.Index = Game;
		});

	_entities->GetOrAddComponent<ZhizhaVolumeComponent>(ZhizhaVolume);

}

ZhizhaVolume_InitSystem::ZhizhaVolume_InitSystem(ResourceManager& resources)
	: _resources(resources) { }
