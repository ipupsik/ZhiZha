#include "TextureResource.h"
#include "SFML/Graphics/Image.hpp"

TextureResource::TextureResource(std::string&& filename) : ResourceFile(std::move(filename)) {
	_texture.loadFromStream(*this);
}
