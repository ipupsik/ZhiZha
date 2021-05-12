#pragma once

#include <string>
#include <vector>
#include "glad/glad.h"
#include "TextureResource.h"

#include "SFML/System/Vector2.hpp"

class ShaderResource {
	void SetProgram();
	void ResetProgram();
	void BindTexture();

	GLuint ShaderID;

public:
	explicit ShaderResource(std::string&& filename);
};