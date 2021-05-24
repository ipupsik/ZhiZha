#pragma once

#include "ResourceFile.h"
#include "glad/glad.h"
#include <SFML/Graphics/Shader.hpp>

class ShaderResource : public ResourceFile {
	sf::Shader _shader;

public:
	sf::Shader* GetShader() { return &_shader; }

	ShaderResource(std::string name, sf::Shader::Type type);
	explicit ShaderResource(const std::string& name);
};

class VertexShaderResource : public ShaderResource {
public:
	explicit VertexShaderResource(std::string&& shaderName);
};

class FragmentShaderResource : public ShaderResource {
public:
	explicit FragmentShaderResource(std::string&& shaderName);
};