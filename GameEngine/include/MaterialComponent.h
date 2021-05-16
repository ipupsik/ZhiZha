#pragma once

#include <vector>

#include "glad/glad.h"
#include "Component.h"

#include "ShaderResource.h"
#include "TextureResource.h"

class MaterialComponent : public ComponentData<MaterialComponent> {
public:
	GLuint _materialId;
	ShaderResource* VertexShader, *FragmentShader;
	std::vector<TextureResource*> Textures;

	//explicit MaterialComponent();

	//void attachVertexShader(std::string&& filename);
	//void attachFragmentShader(std::string&& filename);
	//void attachTexture(std::string&& filename);
};