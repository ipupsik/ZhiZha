#include "Components/TransformComponent.h"
#include "Components/MaterialComponent.h"
#include "Map_InitSystem.h"
#include "Components/MeshComponent.h"
#include <random>
#include <ctime>
#include <Components/SpeedComponent.h>
#include <ComponentDrop.h>
#include <DefinesPhysics.h>
#include "Components/LayerComponent.h"

void Map_InitSystem::OnInit() {
	auto random = std::default_random_engine(time(nullptr));

	//Initialize Components
	Entity& ball = _entities->CreateEntity();
	Entity& floor = _entities->CreateEntity();

	//Setting balls components
	_entities->GetOrAddComponent<LayerComponent>(ball, [](LayerComponent& c) {
		c.Index = Game;
	});
	_entities->GetOrAddComponent<ComponentDrop>(ball);
	_entities->GetOrAddComponent<SpeedComponent>(ball);

	//Setting floor components
	_entities->GetOrAddComponent<MeshComponent>(floor, [](MeshComponent& c) {
		auto rect = new sf::RectangleShape({1000, 10});
		rect->setFillColor(sf::Color::Magenta);
		c.Drawable = rect;
	});
	_entities->GetOrAddComponent<TransformComponent>(floor, [](TransformComponent& c) {
		c.Location = {0, 500};
		c.Scale = { 1, 1 };
	});
	_entities->GetOrAddComponent<LayerComponent>(floor, [](LayerComponent& c) {
		c.Index = Game;
	});

	//Initialize material
	//FIXME shader loading
	//	material.Shader = _resources.GetOrAddResource<ShaderResource>("Circle")->GetShader();
	//	material.Texture = texture;

	for (int i = 1; i <= 1500; i++) {
		auto& copy = _entities->Instantiate(ball);
		auto& transform = _entities->GetOrAddComponent<TransformComponent>(copy);
		_entities->GetOrAddComponent<MeshComponent>(copy, [&](MeshComponent& c) {
			auto circle = new sf::CircleShape(RADIUS);
			const auto texture = _resources.GetOrAddResource<TextureResource>("Circle_Albedo.png")->GetTexture();
			circle->setTexture(texture);
			c.Drawable = circle;
		});

		transform.Scale = {1, 1};
		transform.Angle = 0;
		transform.Location.x = random() % 1000 + (random() % 1000) / 1000;
		transform.Location.y = random() % 1000 + (random() % 1000) / 1000;

		auto speed = _entities->GetComponent<SpeedComponent>(copy);
		speed->Speed.x = (-5 + random() % 10) + (random() % 1000) / 1000;
		speed->Speed.y = (-5 + random() % 10) + (random() % 1000) / 1000;
	}
}

Map_InitSystem::Map_InitSystem(ResourceManager& resources)
	: _resources(resources) { }
