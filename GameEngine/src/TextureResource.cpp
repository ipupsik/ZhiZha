#include "TextureResource.h"
#include "SFML/Graphics/Image.hpp"

TextureResource::TextureResource(std::string&& filename) : ResourceFile(std::move(filename)), _textureId(-1) {
	sf::Image newImage;
	newImage.loadFromStream(*this);
	if (newImage.getPixelsPtr()) {
		glGenTextures(1, &_textureId);
		glBindTexture(GL_TEXTURE_2D, _textureId);
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, newImage.getSize().x, newImage.getSize().y,
				0, GL_RGBA, GL_UNSIGNED_BYTE, newImage.getPixelsPtr());
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
