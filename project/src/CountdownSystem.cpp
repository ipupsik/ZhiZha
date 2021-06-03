#include <ResourceFile.h>
#include <SFML/Graphics/Font.hpp>
#include <Components/RenderedComponent.h>
#include <Components/LayerComponent.h>
#include "CountdownSystem.h"

void CountdownSystem::OnUpdate() {
	auto left = _timeToPlay - _time.Time();

	if (left / _timeToPlay < 0.1)
		_text.setFillColor(sf::Color{232, 39, 39});
	else if (left / _timeToPlay < 0.2)
		_text.setFillColor(sf::Color{232, 143, 39});
	else if (left / _timeToPlay < 0.3)
		_text.setFillColor(sf::Color{220, 232, 39});
	else if (left / _timeToPlay < 0.4)
		_text.setFillColor(sf::Color{95, 232, 39});

	_text.setString("Time left: " + std::to_string(left) + "s");
}

void CountdownSystem::OnInit() {
	const auto fontRes = _resources.GetOrAddResource<ResourceFile>("JetBrainsMono-Regular.ttf");
	_font.loadFromStream(*fontRes);
	_textEntity = &_entities->CreateEntity();
	_entities->GetOrAddComponent<RenderedComponent>(*_textEntity, [&](RenderedComponent& c) {
		_text.setFont(_font);
		_text.setCharacterSize(20);
		_text.setFillColor(sf::Color{43, 232, 39});
		_text.setPosition(0, 60);
		c.DrawableObj = &_text;
	});
	_entities->GetOrAddComponent<LayerComponent>(*_textEntity, [](LayerComponent& c) {
		c.Index = Gui;
	});
}

void CountdownSystem::OnSceneUnload(Scene scene) {
	_entities->DestroyEntity(*_textEntity);
}
