#pragma once

#include <glad/glad.h>

#include "ResourceFile.h"

class TextureResource
{
	GLuint _textureId;
public:
	explicit TextureResource(ResourceFile&& filename);
};