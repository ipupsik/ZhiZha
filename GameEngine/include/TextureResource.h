#pragma once

#include <glad/glad.h>

#include "ResourceFile.h"

class TextureResource : public ResourceFile
{
	GLuint _textureId;
public:
	explicit TextureResource(std::string&& filename);
};