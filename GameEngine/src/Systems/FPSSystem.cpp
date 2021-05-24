#include "Systems/FPSSystem.h"

#include "Components/LayerComponent.h"
#include "Components/MeshComponent.h"

void FPSSystem::OnFixedUpdate() {
	_fps.setString("FPS: "
		+ std::to_string(static_cast<long>((1 / _time.SmoothDeltaTime())))
		+ " / "
		+ std::to_string(_time.SmoothDeltaTime() * 1000) + "ms\n"
		+ "Physics time: " + std::to_string(_time.RealFixedTime()) + "ms\n");
}

void FPSSystem::OnInit() {
	const auto font = _resources.GetOrAddResource<ResourceFile>("JetBrainsMono-Regular.ttf");
	_font.loadFromStream(*font);
	auto& fontEntity = _entities->CreateEntity();
	_entities->GetOrAddComponent<MeshComponent>(fontEntity, [&](MeshComponent& c) {
		_fps.setFont(_font);
		_fps.setCharacterSize(24);
		c.Drawable = &_fps;
	});
	_entities->GetOrAddComponent<LayerComponent>(fontEntity, [](LayerComponent& c) {
		c.Index = Gui;
	});
}
