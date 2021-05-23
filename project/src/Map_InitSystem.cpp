#include "Components/TransformComponent.h"
#include "Components/MaterialComponent.h"
#include "Map_InitSystem.h"
#include "Components/MeshComponent.h"
#include "Components/ComplexCollisionComponent.h"
#include <random>
#include <ctime>
#include <Components/SpeedComponent.h>

void Map_InitSystem::OnInit() {
	auto random = std::default_random_engine(time(nullptr));

	//Initialize Components
	Entity& Map = _entities->CreateEntity();

	//Getting Components
	auto& mesh = _entities->GetOrAddComponent<MeshComponent>(Map);
//	auto& material = _entities->GetOrAddComponent<MaterialComponent>(Map);
	auto& Collision = _entities->GetOrAddComponent<ComplexCollisionComponent>(Map);

	//Initialize mesh
	auto circle = new sf::CircleShape(1);
	auto texture = _resources.GetOrAddResource<TextureResource>("Circle_Albedo.png")->GetTexture();
	circle->setTexture(texture);
	mesh.Drawable = circle;

	//Initialize material
	//FIXME shader loading
//	material.Shader = _resources.GetOrAddResource<ShaderResource>("Circle")->GetShader();
//	material.Texture = texture;

	for (int i = 0; i < 100; i++) {
		auto& copy = _entities->Instantiate(Map);
		auto& transform = _entities->GetOrAddComponent<TransformComponent>(copy);
		auto& speed = _entities->GetOrAddComponent<SpeedComponent>(copy);

		//Initialize components
		speed.Speed.x = (random() % 1000) / 1000.0f;

		transform.Location = { (random() % 1000) + (random() % 100) / 100.0f,
				(random() % 1000) + (random() % 100) / 100.0f };
		transform.Scale = { 5, 5 };
		transform.Angle = 0;
	}
}
Map_InitSystem::Map_InitSystem(ResourceManager& resources)
		:_resources(resources) { }
