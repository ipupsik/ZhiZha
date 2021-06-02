#include "TextureResource.h"
#include "SFML/Graphics/Image.hpp"

TextureResource::TextureResource(std::string&& filename) :ResourceFile(std::move(filename)), TextureId(-1) {
	Texture.loadFromStream(*this);
	TextureId = Texture.getNativeHandle();
	Texture.setRepeated(true);
	Texture.setSrgb(true);
	Texture.generateMipmap();
}
