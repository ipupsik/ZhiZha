#include <FontResource.h>
#include "Systems/FPSSystem.h"
#include "ResourceFile.h"
#include "Components/LayerComponent.h"
#include "Components/RenderedComponent.h"

void FPSSystem::OnFixedUpdate() {
	if (_fontEntity->IsActive())
		_fps.setString("FPS: "
				+ std::to_string(static_cast<long>((1 / _time.SmoothDeltaTime())))
				+ " / "
				+ std::to_string(_time.SmoothDeltaTime() * 1000) + "ms\n"
				+ "Physics time: " + std::to_string(_time.RealFixedTime()) + "ms\n");
}

void FPSSystem::OnInit() {
	auto& font = _resources.GetOrAddResource<FontResource>("JetBrainsMono-Regular")->Font();
	_fontEntity = &_entities->CreateEntity();
	_fontEntity->SetActive(false);
	_entities->GetOrAddComponent<RenderedComponent>(*_fontEntity, [&](RenderedComponent& c) {
		_fps.setFont(font);
		_fps.setCharacterSize(20);
		c.DrawableObj = &_fps;
	});
	_entities->GetOrAddComponent<LayerComponent>(*_fontEntity, [](LayerComponent& c) {
		c.Index = Gui;
	});
}

void FPSSystem::OnUpdate() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
		_wasF3Pressed = true;
	else {
		if (_wasF3Pressed)
			_fontEntity->SetActive(!_fontEntity->IsActive());
		_wasF3Pressed = false;
	}
}

void FPSSystem::OnSceneUnload(Scene scene) {
	_entities->DestroyEntity(*_fontEntity);
}
