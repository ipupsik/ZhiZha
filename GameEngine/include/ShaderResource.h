#pragma once

#include "ResourceFile.h"
#include "glad/glad.h"
#include <SFML/Graphics/Shader.hpp>

class ShaderResource : public ResourceFile {
public:
	GLuint _shaderId;

	void LoadShader(GLuint type);
	ShaderResource(std::string&& shaderName);
};

class VertexShaderResource : public ShaderResource {
public:
	explicit VertexShaderResource(std::string&& shaderName);
};

class FragmentShaderResource : public ShaderResource {
public:
	explicit FragmentShaderResource(std::string&& shaderName);
};