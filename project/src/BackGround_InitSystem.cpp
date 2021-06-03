#include "Components/MaterialComponent.h"
#include "Components/RenderedComponent.h"
#include "BackGround_InitSystem.h"
#include <random>
#include "Components/LayerComponent.h"

void BackGround_InitSystem::OnInit() {
	//Initialize Enityty
	_background = &_entities->CreateEntity();

	_entities->GetOrAddComponent<LayerComponent>(*_background, [](LayerComponent& c) {
		c.Index = Background;
	});

	_entities->GetOrAddComponent<RenderedComponent>(*_background, [&](RenderedComponent& c) {
		auto texture = _resources.GetOrAddResource<TextureResource>("lava.jpg");
		auto lava = new sf::Sprite(texture->Texture);
		lava->setTextureRect({150, 0, 900, 900});
		c.DrawableObj = lava;
	});
}

BackGround_InitSystem::BackGround_InitSystem(ResourceManager& resources)
		:_resources(resources) { }

void BackGround_InitSystem::OnSceneUnload(Scene scene) {
	_entities->DestroyEntity(*_background);
}
