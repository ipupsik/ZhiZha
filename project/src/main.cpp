#include "GL/glew.h"
#include "MeshResource.h"
#include "SFML/Window/Window.hpp"

int main() {
	sf::Window window(sf::VideoMode(800, 600), "Sample");
	glewInit();
	MeshResource res("Circle.obj");
}
