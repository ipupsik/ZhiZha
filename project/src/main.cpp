#include "Engine.h"
#include "TextureResource.h"
#include "SFML/Window/Window.hpp"

int main() {
	sf::Window window(sf::VideoMode(800, 600), "Sample");
	gladLoadGL();
	
	Engine(std::move(window)).Start();
}
