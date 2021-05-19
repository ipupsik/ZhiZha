#include "Map_InitSystem.h"
#include "Components/ActorComponent.h"
#include "Components/ComplexCollisionComponent.h"

void Map_InitSystem::OnInit()
{
	//Initialize Components
	Entity &Map = _entities->CreateEntity();
	_entities->GetOrAddComponent<ActorComponent>(Map);
	_entities->GetOrAddComponent<ComplexCollisionComponent>(Map);
	//---

	//Getting Components
	auto Actor = _entities->GetComponent<ActorComponent>(Map);
	auto Collision = _entities->GetComponent<ComplexCollisionComponent>(Map);

	//Initialize mesh
	Actor->Mesh = new MeshResource("Map");

	//Initialize material
	Actor->Material.VertexShader = new VertexShaderResource("Map");
	Actor->Material.FragmentShader = new FragmentShaderResource("Map");
	Actor->Material.Textures.emplace_back(new TextureResource("Map_Albedo.png"));
	Actor->Material.attributesCount = 2;

	GLint ok;
	GLchar log[2000];
	Actor->Material._materialId = glCreateProgram();
	glAttachShader(Actor->Material._materialId, Actor->Material.FragmentShader->_shaderId);
	glAttachShader(Actor->Material._materialId, Actor->Material.VertexShader->_shaderId);
	glLinkProgram(Actor->Material._materialId);
	glGetProgramiv(Actor->Material._materialId, GL_LINK_STATUS, &ok);
	if (!ok)
	{
		glGetProgramInfoLog(Actor->Material._materialId, 2000, NULL, log);
		printf("\n");
	}

	//Initialize Transform
	Actor->Transform.Location = { 0.0f, 0.0f };
	Actor->Transform.Scale = { 1.0f, 1.0f };
	Actor->Transform.Rotation = { 0.0f, 0.0f };

	Actor->parent = nullptr;
}