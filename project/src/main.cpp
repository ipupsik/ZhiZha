#include "MeshResource.h"
#include "TextureResource.h"
#include "ShaderResource.h"
#include "SFML/Window/Window.hpp"

int main() {
	sf::Window window(sf::VideoMode(800, 600), "Sample");
	gladLoadGL();

	MeshResource res("Circle");
	TextureResource res2("Circle_Albedo");
	ShaderResource res3("Circle");
}
