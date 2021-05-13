#include <chrono>

#include "ResourceFile.h"
#include "MeshResource.h"
#include "TextureResource.h"
#include "ShaderResource.h"
#include "SFML/Window/Window.hpp"

using namespace std::chrono_literals;

int main() {
	sf::Window window(sf::VideoMode(800, 600), "Sample");
	gladLoadGL();
	
	MeshResource res("Circle.obj");
	TextureResource res2("Circle_Albedo.png");
	ShaderResource res3("Circle");
}
