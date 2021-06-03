#include "Components/SpriteComponent.h"
#include <TextureResource.h>
#include <Components/RenderedComponent.h>
#include <Components/LayerComponent.h>
#include <Components/ButtonComponent.h>
#include "MenuSystem.h"

void MenuSystem::OnInit() {
	auto& backEntity = _entities->CreateEntity();
	auto& startEntity = _entities->CreateEntity();
	auto& endEntity = _entities->CreateEntity();

	_createdEntities.assign({&backEntity, &startEntity, &endEntity});

	auto menuBackground = _resources.GetOrAddResource<TextureResource>("background.jpg");
	auto menuStart = _resources.GetOrAddResource<TextureResource>("start_game.jpg");
	auto menuExit = _resources.GetOrAddResource<TextureResource>("exit.jpg");

	_entities->GetOrAddComponent<SpriteComponent>(backEntity, [&](SpriteComponent& c) {
		c.Sprite = new sf::Sprite(menuBackground->Texture);
		c.Sprite->setPosition(0, 0);

		_entities->GetOrAddComponent<LayerComponent>(backEntity).Index = Background;
		_entities->GetOrAddComponent<RenderedComponent>(backEntity).DrawableObj = c.Sprite;
	});

	_entities->GetOrAddComponent<SpriteComponent>(startEntity, [&](SpriteComponent& c) {
		c.Sprite = new sf::Sprite(menuStart->Texture);
		c.Sprite->setPosition(330, 300);

		_entities->GetOrAddComponent<LayerComponent>(startEntity).Index = Gui;
		_entities->GetOrAddComponent<RenderedComponent>(startEntity).DrawableObj = c.Sprite;

		_entities->GetOrAddComponent<ButtonComponent>(startEntity, [&](ButtonComponent& cc) {
			cc.Bounds = sf::IntRect(c.Sprite->getGlobalBounds());
			cc.OnClick = [*this] {
				_engine.UnloadScene();
				_engine.LoadScene(Scene::Main);
			};
		});
	});

	_entities->GetOrAddComponent<SpriteComponent>(endEntity, [&](SpriteComponent& c) {
		c.Sprite = new sf::Sprite(menuExit->Texture);
		c.Sprite->setPosition(380, 400);

		_entities->GetOrAddComponent<LayerComponent>(endEntity).Index = Gui;
		_entities->GetOrAddComponent<RenderedComponent>(endEntity).DrawableObj = c.Sprite;

		_entities->GetOrAddComponent<ButtonComponent>(endEntity, [&](ButtonComponent& cc) {
			cc.Bounds = sf::IntRect(c.Sprite->getGlobalBounds());
			cc.OnClick = [*this] {
				_engine.UnloadScene();
				_engine.Stop();
				_window.close();
			};
		});
	});
}

void MenuSystem::OnUpdate() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		_engine.UnloadScene();
		_engine.LoadScene(Scene::Main);
	}
}

void MenuSystem::OnSceneUnload(Scene scene) {
#pragma unroll 3
	for (auto item: _createdEntities)
		_entities->DestroyEntity(*item);
}