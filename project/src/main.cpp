#include "Systems/RenderSystem_HUD.h"
#include "Systems/RenderSystem_Models.h"
#include "Systems/MoveSystem.h"
#include "DefinesPhysics.h"
#include "Zhizha_InitSystem.h"
#include "Map_InitSystem.h"
#include "Engine.h"
#include "Components/LayerComponent.h"
#include "glad/glad.h"

#include "Systems/CollisionSystem.h"
#include "Systems/EventSystem.h"
#include "Systems/FPSSystem.h"
#include "Systems/GravitationSystem.h"
#include "Systems/RotateSystem.h"
#include "Systems/ResetParamsSystem.h"
#include "Systems/MaterialAttachSystem.h"
#include "Systems/UnionDropsSystem.h"
#include "Systems/ForceCalculationSystem.h"
#include "Systems/ShiftDropsSystem.h"
#include "Systems/TestSystem.h"
#include "BackGround_InitSystem.h"

#include "ZhizhaVolume_InitSystem.h"
#include "FormZhizhaVolume_System.h"
#include "SmallBrunch_InitSystem.h"
#include "SmallSkull_InitSystem.h"
#include "Grass_InitSystem.h"
#include "Stone_1_InitSystem.h"
#include "Stone_2_InitSystem.h"
#include "Tree_1_InitSystem.h"
#include "Tree_2_InitSystem.h"
#include "Tree_3_InitSystem.h"

#if defined(linux)
#include <X11/Xlib.h>
#endif

int main() {
#if defined(linux)
	XInitThreads();
#endif
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 0;

	auto window = sf::RenderWindow(sf::VideoMode(1080, 720), "Sample", sf::Style::Default,
			settings);

	gladLoadGL();

	glScalef(1, 1080.0f / 720.0f, 1);

	sf::Vector2f gravity = { 0, G / 20 };
	sf::Vector2f camera_location = { 0.0f, 0.0f };
	float global_phi = 0;
	std::vector views = {
			window.getDefaultView(), // game view
			window.getDefaultView() // gui view
	};

	views.at(Game).zoom(3);

	auto engine = new Engine(window);
	engine->RegisterSystem<BackGround_InitSystem>(engine->GetResourceManager())
		.RegisterSystem<Grass_InitSystem>(engine->GetResourceManager())
		.RegisterSystem<SmallBrunch_InitSystem>(engine->GetResourceManager())
		.RegisterSystem<Tree_1_InitSystem>(engine->GetResourceManager())
		.RegisterSystem<Tree_2_InitSystem>(engine->GetResourceManager())
		.RegisterSystem<Tree_3_InitSystem>(engine->GetResourceManager())
		.RegisterSystem<Stone_1_InitSystem>(engine->GetResourceManager())
		.RegisterSystem<Stone_2_InitSystem>(engine->GetResourceManager())
		.RegisterSystem<SmallSkull_InitSystem>(engine->GetResourceManager())
		.RegisterSystem<Zhizha_InitSystem>(engine->GetResourceManager())
		.RegisterSystem<Map_InitSystem>(engine->GetResourceManager())
		.RegisterSystem<ZhizhaVolume_InitSystem>(engine->GetResourceManager())

		.RegisterSystem<MaterialAttachSystem>(window)
		.RegisterSystem<RotateSystem>(views[Game], gravity, engine->GetTime(), global_phi)
		.RegisterSystem<EventSystem>(window, views[Game])
		.RegisterSystem<FPSSystem>(engine->GetTime(), engine->GetResourceManager())

		.RegisterSystem<FormZhizhaVolume_System>()
		.RegisterSystem<RenderSystem_Models>(window, views, camera_location, global_phi)
		.RegisterSystem<RenderSystem_HUD>(window, views)


		.RegisterSystem<CollisionSystem>()
		.RegisterSystem<UnionDropsSystem>(window)
		.RegisterSystem<GravitationSystem>(engine->GetTime(), gravity)
		.RegisterSystem<ForceCalculationSystem>(engine->GetTime(), gravity)
		.RegisterSystem<ShiftDropsSystem>(engine->GetTime())
		.RegisterSystem<TestSystem>()
		.RegisterSystem<ResetParamsSystem>();
	engine->Start();
}
