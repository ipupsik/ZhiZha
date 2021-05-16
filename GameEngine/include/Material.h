#pragma once

#include <vector>

#include "glad/glad.h"

#include "ShaderResource.h"
#include "TextureResource.h"

class Material {
	GLuint _materialId;
	ShaderResource* VertexShader, *FragmentShader;
	std::vector<TextureResource*> Textures;

public:
	explicit Material();

	void attachVertexShader(std::string&& filename);
	void attachFragmentShader(std::string&& filename);
	void attachTexture(std::string&& filename);
};