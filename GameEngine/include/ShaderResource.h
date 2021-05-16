#pragma once

#include "ResourceFile.h"
#include "glad/glad.h"

class ShaderResource : public ResourceFile {
	GLuint _shaderId;

public:
	GLuint LoadShader(GLuint type);
	explicit ShaderResource(std::string&& shaderName);
};

class VertexShaderResource : public ShaderResource {
public:
	explicit VertexShaderResource(std::string&& shaderName);
};

class FragmentShaderResource : public ShaderResource {
public:
	explicit FragmentShaderResource(std::string&& shaderName);
};