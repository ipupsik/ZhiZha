#pragma once

#include <vector>

#include "glad/glad.h"
#include "Component.h"
#include "SFML/Graphics.hpp"
#include "ShaderResource.h"
#include "TextureResource.h"

class MaterialComponent : public ComponentData<MaterialComponent> {
public:
	GLuint _materialId;
	GLuint attributesCount;
	ShaderResource* VertexShader, * FragmentShader;
	std::vector<TextureResource*> Textures;
};