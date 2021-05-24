#include "Components/TransformComponent.h"
#include "Components/MaterialComponent.h"
#include "Map_InitSystem.h"
#include "Components/MeshComponent.h"
#include "Components/MeshCollider.h"
#include <random>
#include <ctime>
#include <Components/SpeedComponent.h>
#include <ComponentDrop.h>
#include "Components/LayerComponent.h"

void Map_InitSystem::OnInit() {
	auto random = std::default_random_engine(time(nullptr));

	//Initialize Components
	Entity& ball = _entities->CreateEntity();
	Entity& floor = _entities->CreateEntity();

	//Setting balls components
	_entities->GetOrAddComponent<MeshComponent>(ball, [&](MeshComponent& c) {
		auto circle = new sf::CircleShape(2);
		const auto texture = _resources.GetOrAddResource<TextureResource>("Circle_Albedo.png")->GetTexture();
		circle->setTexture(texture);
		c.Drawable = circle;
	});
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
		c.Location = {0, 400};
		c.Scale = { 1, 1 };
	});
	_entities->GetOrAddComponent<LayerComponent>(floor, [](LayerComponent& c) {
		c.Index = Game;
	});

	//Initialize material
	//FIXME shader loading
	//	material.Shader = _resources.GetOrAddResource<ShaderResource>("Circle")->GetShader();
	//	material.Texture = texture;

	for (int i = 0; i < 100; i++) {
		auto& copy = _entities->Instantiate(ball);
		auto& transform = _entities->GetOrAddComponent<TransformComponent>(copy);

		transform.Location = {
			(random() % 1000) + (random() % 100) / 100.0f,
			(random() % 1000) + (random() % 100) / 100.0f
		};
		transform.Scale = {5, 5};
		transform.Angle = 0;
	}
}

Map_InitSystem::Map_InitSystem(ResourceManager& resources)
	: _resources(resources) { }
