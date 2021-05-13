#pragma once

#include "ResourceFile.h"
#include "glad/glad.h"

class ShaderResource {
	GLuint _shaderId;

public:
	explicit ShaderResource(std::string&& shaderName);
};