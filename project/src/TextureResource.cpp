#include "TextureResource.h"
#include "SFML/Graphics/Image.hpp"

TextureResource::TextureResource(std::string&& filename) : TextureID(-1)
{
    std::string name  = (filename + ".png");
    sf::Image newImage;
    newImage.loadFromFile(name);
    if (newImage.getPixelsPtr())
    {
        glGenTextures(1, &TextureID);
        glBindTexture(GL_TEXTURE_2D, TextureID);
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, newImage.getSize().x, newImage.getSize().y,
                0, 4 == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, newImage.getPixelsPtr());
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}