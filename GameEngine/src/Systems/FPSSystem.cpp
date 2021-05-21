#include "Systems/FPSSystem.h"

#include <iostream>

void FPSSystem::OnPostUpdate() {
	_window.draw(_fps);
}

void FPSSystem::OnFixedUpdate() {
	_fps.setString("FPS: "
		+ std::to_string(static_cast<long>((1 / _time.SmoothDeltaTime())))
		+ " / "
		+ std::to_string(_time.SmoothDeltaTime()) + "ms\n");
}
