#pragma once

#include <string>
#include <vector>
#include <glad/glad.h>

#include "SFML/System/Vector2.hpp"

class TextureResource
{
	GLuint TextureID;
public:
	explicit TextureResource(std::string&& filename);
};