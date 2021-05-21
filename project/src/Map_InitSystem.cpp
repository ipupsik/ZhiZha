#include "Map_InitSystem.h"

#include "Components/ActorComponent.h"
#include "Components/MeshComponent.h"
#include "Components/ComplexCollisionComponent.h"

void Map_InitSystem::OnInit()
{
	//Initialize Components
	Entity &Map = _entities->CreateEntity();
	
	//Getting Components
	auto& mesh = _entities->GetOrAddComponent<MeshComponent>(Map);
	auto& transform = _entities->GetOrAddComponent<TransformComponent>(Map);
	auto& material = _entities->GetOrAddComponent<MaterialComponent>(Map);
	auto& Collision = _entities->GetOrAddComponent<ComplexCollisionComponent>(Map);

	//Initialize mesh
	mesh.Mesh = _resources.GetOrAddResource<MeshResource>("Map");

	//Initialize material
	material.VertexShader = _resources.GetOrAddResource<VertexShaderResource>("Map");
	material.FragmentShader = _resources.GetOrAddResource<FragmentShaderResource>("Map");
	material.Textures.emplace_back(_resources.GetOrAddResource<TextureResource>("Map_Albedo.png"));
	material.attributesCount = 2;

	GLint ok;
	GLchar log[2000];
	material._materialId = glCreateProgram();
	glAttachShader(material._materialId, material.FragmentShader->_shaderId);
	glAttachShader(material._materialId, material.VertexShader->_shaderId);
	glLinkProgram(material._materialId);
	glGetProgramiv(material._materialId, GL_LINK_STATUS, &ok);
	if (!ok)
	{
		glGetProgramInfoLog(material._materialId, 2000, NULL, log);
		printf("\n");
	}

	//Initialize Transform
	transform.Location = { 0.0f, 0.0f };
	transform.Scale = { 1.0f, 1.0f };
	transform.Rotation = { 0.0f, 0.0f };
}
Map_InitSystem::Map_InitSystem(ResourceManager& resources)
		:_resources(resources) { }
