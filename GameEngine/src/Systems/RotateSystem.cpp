#include "Systems/RotateSystem.h"

#include <iostream>

#include "SFML/Window/Keyboard.hpp"
#include "utils.h"
#include "../../../PhysicsEngine/include/DefinesPhysics.h"
#include "Components/MeshComponent.h"

using namespace sf::Extensions::Vector2;

void RotateSystem::OnFixedUpdate() {
	_dphi = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		_dphi = -300 / (std::abs(_phi) + 10);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		_dphi = 300 / (std::abs(_phi) + 10);

	if (std::abs(_phi) < 1)
		_ddphi = 0;
	else if (_phi > 0)
		_ddphi = -500;
	else
		_ddphi = 500;

	const auto deltaPhi = _dphi * _time.FixedDeltaTime() + _ddphi * _time.FixedDeltaTime() * _time.FixedDeltaTime() / 2;
	_phi += deltaPhi;
	
	_gameView.setRotation(_phi);
	_gravitation = _gravitation->*RotateDeg(deltaPhi);
}
