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
	auto& material = _entities->GetOrAddComponent<MaterialComponent>(Map);
	auto& Collision = _entities->GetOrAddComponent<ComplexCollisionComponent>(Map);

	//Initialize mesh
	auto& map = *_resources.GetOrAddResource<MeshResource>("Circle");
	mesh.Buffer = const_cast<sf::VertexBuffer*>(&map.VBO());
	mesh.Elements = map.EBO();
	mesh.FacesSize = map.Faces();

	//Initialize material
	//FIXME shader loading
	//material.Shader = _resources.GetOrAddResource<FragmentShaderResource>("Circle")->GetShader();
	material.Texture = _resources.GetOrAddResource<TextureResource>("Circle_Albedo.png")
			->GetTexture();

	for (int i = 0; i < 10000; i++) {
		auto& copy = _entities->Instantiate(Map);
		auto& transform = _entities->GetOrAddComponent<TransformComponent>(copy);
		auto& speed = _entities->GetOrAddComponent<SpeedComponent>(copy);

		//Initialize components
		speed.Speed = (random() % 1000) / 1000.0f;

		transform.Location = { (random() % 1000) + (random() % 100) / 100.0f,
				(random() % 1000) + (random() % 100) / 100.0f };
		transform.Scale = { 100, 100 };
		transform.Angle = 0;
	}
}
Map_InitSystem::Map_InitSystem(ResourceManager& resources)
		:_resources(resources) { }
