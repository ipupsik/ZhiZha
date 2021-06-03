#include "Components/SpriteComponent.h"
#include <Components/RenderedComponent.h>
#include <Components/LayerComponent.h>
#include <Components/ButtonComponent.h>
#include "MenuSystem.h"
#include "FontResource.h"

void MenuSystem::OnInit() {
	auto& startEntity = _entities->CreateEntity();
	auto& endEntity = _entities->CreateEntity();
	auto& namingEntity = _entities->CreateEntity();

	_createdEntities.assign({ &startEntity, &endEntity, &namingEntity });

	auto& font = _resources.GetOrAddResource<FontResource>("JetBrainsMono-Regular")->Font();

	_startText.setCharacterSize(48);
	_startText.setFont(font);
	_startText.setString("Start game");
	_startText.setPosition(300, 350);

	_endText.setCharacterSize(48);
	_endText.setFont(font);
	_endText.setString("Exit");
	_endText.setPosition(300, 404);

	_namingText.setCharacterSize(64);
	_namingText.setFont(font);
	_namingText.setString("ZhiZha");
	_namingText.setPosition(250, 250);

	_entities->GetOrAddComponent<RenderedComponent>(namingEntity).DrawableObj = &_namingText;
	_entities->GetOrAddComponent<LayerComponent>(namingEntity).Index = Gui;

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

void MenuSystem::OnUpdate() {
	_window.clear(sf::Color{144, 144, 144});
}
