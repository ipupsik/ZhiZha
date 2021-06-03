#include "Components/SpriteComponent.h"
#include <TextureResource.h>
#include <Components/RenderedComponent.h>
#include <Components/LayerComponent.h>
#include <Components/ButtonComponent.h>
#include "MenuSystem.h"
#include "FontResource.h"

void MenuSystem::OnInit() {
	auto& backEntity = _entities->CreateEntity();
	auto& startEntity = _entities->CreateEntity();
	auto& endEntity = _entities->CreateEntity();

	_createdEntities.assign({ &backEntity, &startEntity, &endEntity });

	auto menuBackground = _resources.GetOrAddResource<TextureResource>("background.jpg");
	auto& font = _resources.GetOrAddResource<FontResource>("JetBrainsMono-Regular")->Font();

	_startText.setCharacterSize(48);
	_startText.setFont(font);
	_startText.setString("Start game");
	_startText.setPosition(300, 350);

	_endText.setCharacterSize(48);
	_endText.setFont(font);
	_endText.setString("Exit");
	_endText.setPosition(300, 404);

	_entities->GetOrAddComponent<SpriteComponent>(backEntity, [&](SpriteComponent& c) {
		c.Sprite = new sf::Sprite(menuBackground->Texture);
		c.Sprite->setPosition(0, 0);

		_entities->GetOrAddComponent<LayerComponent>(backEntity).Index = Background;
		_entities->GetOrAddComponent<RenderedComponent>(backEntity).DrawableObj = c.Sprite;
	});

	_entities->GetOrAddComponent<LayerComponent>(startEntity).Index = Gui;
	_entities->GetOrAddComponent<RenderedComponent>(startEntity).DrawableObj = &_startText;

	_entities->GetOrAddComponent<ButtonComponent>(startEntity, [&](ButtonComponent& cc) {
		cc.Bounds = sf::IntRect(_startText.getGlobalBounds());
		cc.OnClick = [&] {
			_engine.UnloadScene();
			_engine.LoadScene(Scene::Main);
		};
		cc.OnHover = [&] {
			_startText.setFillColor(sf::Color{ 72, 72, 72 });
		};
		cc.OnHoverEnds = [&] {
			_startText.setFillColor(sf::Color::White);
		};
	});

	_entities->GetOrAddComponent<LayerComponent>(endEntity).Index = Gui;
	_entities->GetOrAddComponent<RenderedComponent>(endEntity).DrawableObj = &_endText;

	_entities->GetOrAddComponent<ButtonComponent>(endEntity, [&](ButtonComponent& cc) {
		cc.Bounds = sf::IntRect(_endText.getGlobalBounds());
		cc.OnClick = [*this] {
			_engine.UnloadScene();
			_engine.Stop();
			_window.close();
		};
		cc.OnHover = [&] {
			_endText.setFillColor(sf::Color{ 72, 72, 72 });
		};
		cc.OnHoverEnds = [&] {
			_endText.setFillColor(sf::Color::White);
		};
	});
}

void MenuSystem::OnSceneUnload(Scene scene) {
#pragma unroll 3
	for (auto item: _createdEntities)
		_entities->DestroyEntity(*item);
}