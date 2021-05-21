#include "Systems/FPSSystem.h"

#include <iostream>

void FPSSystem::OnPostUpdate() {
	std::cout << "FPS: " << 1 / _time.DeltaTime() << "															\r";
}
