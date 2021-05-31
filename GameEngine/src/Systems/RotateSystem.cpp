#include "Systems/RotateSystem.h"
#include "Components/MeshComponent.h"
#include <iostream>
#include <Components/TransformComponent.h>
#include <Components/LayerComponent.h>

#include "SFML/Window/Keyboard.hpp"
#include "utils.h"
#include "../../../PhysicsEngine/include/DefinesPhysics.h"

using namespace sf::Extensions::Vector2;

void RotateSystem::OnFixedUpdate() {
	_dphi = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		_dphi = -900 / 1000.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		_dphi = 900 / 1000.0f;

	_phi += _dphi;
	
	_gravitation = sf::Vector2f{0, -G / 20}->*RotateDeg(-_phi);
}
