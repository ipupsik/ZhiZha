#include <Components/TransformComponent.h>
#include <Components/SpeedComponent.h>
#include <Components/RenderedComponent.h>
#include "HappyEndSystem.h"
#include "FontResource.h"
#include <random>
#include <Components/LayerComponent.h>
#include "utils.h"
#include "NameComponent.h"

using namespace sf::Extensions::Vector2;

void HappyEndSystem::OnUpdate() {
	const auto& items = _entities->GetEntitiesBy<SpeedComponent, TransformComponent>();
	for (const auto& item: items) {
		auto& [speed, transform] = item.Components;

		transform->Location += speed->Speed;
	}

	_window.clear(sf::Color{ 187, 226, 237 });
}

void HappyEndSystem::OnInit() {
	auto rnd = std::default_random_engine();
	auto& font = _resources.GetOrAddResource<FontResource>("JetBrainsMono-Regular")->Font();
	const auto& items = _entities->GetEntitiesBy<NameComponent>();
	const auto& way = items[0];
	auto& [name] = way.Components;

	_gameOver.setFont(font);
	if (name->Name == "Win")
		_gameOver.setString("You win!");
	else if (name->Name == "Loose")
		_gameOver.setString("You loose");
	_gameOver.setPosition(300, 300);
	_gameOver.setCharacterSize(64);
	_gameOver.setFillColor(sf::Color::Black);

	auto& rectPrototype = _entities->CreateEntity();
	rectPrototype.SetActive(false);

	_entities->GetOrAddComponent<LayerComponent>(rectPrototype).Index = Game;

	if (name->Name == "Win") {
		for (int i = 0; i < 500; i++) {
			auto& rect = _entities->Instantiate(rectPrototype);
			_createdEntities.push_back(&rect);
			_entities->GetOrAddComponent<TransformComponent>(rect, [&](TransformComponent& c) {
				c.Angle = rnd() % 360 + 1 / (1 + rnd());
				c.Scale = { 1.f + (rnd() % 4) * 0.1f, 1.f + (rnd() % 4) * 0.1f };
				c.Location = {
						static_cast<float>(50 + rnd() % 50 + (rnd() % 500) / (i + 1)),
						static_cast<float>(i * 2 - 200 + rnd() % 200 + (rnd() % 500) / (i + 1)) };
				_entities->GetOrAddComponent<SpeedComponent>(rect, [&](SpeedComponent& cc) {
					cc.Speed = (sf::Vector2f{ 450, 0 } - c.Location)->*Normalize()
							* static_cast<float>(1 + rnd() % 9);
				});
			});
			_entities->GetOrAddComponent<RenderedComponent>(rect, [&](RenderedComponent& c) {
				auto shape = new sf::RectangleShape({ 10, 20 });
				shape->setFillColor(sf::Color{
					static_cast<sf::Uint8>(rnd() % 256),
					static_cast<sf::Uint8>(rnd() % 256),
					static_cast<sf::Uint8>(rnd() % 256) });
				c.DrawableObj = shape;
			});
		}
		for (int i = 0; i < 500; i++) {
			auto& rect = _entities->Instantiate(rectPrototype);
			_createdEntities.push_back(&rect);
			_entities->GetOrAddComponent<TransformComponent>(rect, [&](TransformComponent& c) {
				c.Angle = rnd() % 360 + 1 / (1 + rnd());
				c.Scale = { 1.f + (rnd() % 4) * 0.1f, 1.f + (rnd() % 4) * 0.1f };
				c.Location = {
						static_cast<float>(850 + rnd() % 50 + (rnd() % 500) / (i + 1)),
						static_cast<float>(i * 2 - 200 + rnd() % 200 + (rnd() % 500) / (i + 1)) };
				_entities->GetOrAddComponent<SpeedComponent>(rect, [&](SpeedComponent& cc) {
					cc.Speed = (sf::Vector2f{ 450, 0 } - c.Location)->*Normalize()
							* static_cast<float>(1 + rnd() % 6);
				});
			});
			_entities->GetOrAddComponent<RenderedComponent>(rect, [&](RenderedComponent& c) {
				auto shape = new sf::RectangleShape({ 10, 20 });
				shape->setFillColor(sf::Color{
					static_cast<sf::Uint8>(rnd() % 256),
					static_cast<sf::Uint8>(rnd() % 256),
					static_cast<sf::Uint8>(rnd() % 256) });
				c.DrawableObj = shape;
			});
		}

		_createdEntities.push_back(&rectPrototype);
	}

	auto& textEntity = _entities->CreateEntity();
	_entities->GetOrAddComponent<RenderedComponent>(textEntity).DrawableObj = &_gameOver;
	_entities->GetOrAddComponent<LayerComponent>(textEntity).Index = Gui;

	_createdEntities.push_back(&textEntity);
}

void HappyEndSystem::OnSceneUnload(Scene scene) {
	for (auto item: _createdEntities)
		_entities->DestroyEntity(*item);
}
