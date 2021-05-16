#pragma once

#include "ResourceFile.h"
#include "glad/glad.h"

class ShaderResource : public ResourceFile {
public:
	GLuint _shaderId;

	virtual void LoadShader(GLuint type) = 0;
	explicit ShaderResource(std::string&& shaderName);
};

class VertexShaderResource : public ShaderResource {
public:
	explicit VertexShaderResource(std::string&& shaderName);
	virtual void LoadShader(GLuint type);
};

class FragmentShaderResource : public ShaderResource {
public:
	explicit FragmentShaderResource(std::string&& shaderName);
	virtual void LoadShader(GLuint type);
};