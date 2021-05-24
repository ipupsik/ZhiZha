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
		_dphi = -600 / (std::abs(_phi) + 10);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		_dphi = 600 / (std::abs(_phi) + 10);

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
	_line->setRotation(asin(_gravitation->*Sin(sf::Vector2f{0, 1})));
}

void RotateSystem::OnInit() {
	_line = new sf::RectangleShape({10, 40});
	_line->setFillColor(sf::Color::Yellow);

	auto& line = _entities->CreateEntity();
	_entities->GetOrAddComponent<MeshComponent>(line, [&](MeshComponent& c) {
		c.Drawable = _line;
	});
	_entities->GetOrAddComponent<TransformComponent>(line, [](TransformComponent& c) {
		c.Location = {40, 40};
		c.Scale = {1, 1};
	});
	_entities->GetOrAddComponent<LayerComponent>(line, [](LayerComponent& c) {
		c.Index = Gui;
	});
}
