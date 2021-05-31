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

void ZhizhaVolume_InitSystem::OnInit()
{
	Entity& ZhizhaVolume = _entities->CreateEntity();

	_entities->GetOrAddComponent<MaterialComponent>(ZhizhaVolume, [&](MaterialComponent& c) {
		c.VertexShader = _resources.GetOrAddResource<VertexShaderResource>("Zhizha");
		c.FragmentShader = _resources.GetOrAddResource<FragmentShaderResource>("Zhizha");
		c.Textures.emplace_back(_resources.GetOrAddResource<TextureResource>("Circle_Albedo.png"));
		c.attributesCount = 2;
		});

	_entities->GetOrAddComponent<LayerComponent>(ZhizhaVolume, [](LayerComponent& c) {
		c.Index = Game;
		});

	_entities->GetOrAddComponent<ZhizhaVolumeComponent>(ZhizhaVolume, [](ZhizhaVolumeComponent& c) {
		glGenBuffers(1, &c.indexVBO);
		glBindBuffer(GL_ARRAY_BUFFER, c.indexVBO);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(sf::Vector2f) * c.vertices[c.side].size(), c.vertices[c.side].begin()._Ptr, GL_DYNAMIC_DRAW);
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &c.indexEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sf::Vector2f) * c.vertices[c.side].size(), c.vertices[c.side].begin()._Ptr, GL_DYNAMIC_DRAW);
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glGenVertexArrays(1, &c.indexVAO);
		glBindVertexArray(c.indexVAO);
		{
			glBindBuffer(GL_ARRAY_BUFFER, c.indexVBO);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		glBindVertexArray(0);
		});
}

ZhizhaVolume_InitSystem::ZhizhaVolume_InitSystem(ResourceManager& resources)
	: _resources(resources) { }
