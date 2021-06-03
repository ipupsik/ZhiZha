#include "Systems/RenderSystem.h"
#include "Systems/EndSystem.h"
#include "DefinesPhysics.h"
#include "Zhizha_InitSystem.h"
#include "Map_InitSystem.h"
#include "Engine.h"
#include "Components/LayerComponent.h"
#include "glad/glad.h"
#include "Systems/ButtonClickSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/EventSystem.h"
#include "Systems/CameraMovingSystem.h"
#include "Systems/FPSSystem.h"
#include "Systems/GravitationSystem.h"
#include "Systems/RotateSystem.h"
#include "Systems/ResetParamsSystem.h"
#include "Systems/MaterialAttachSystem.h"
#include "Systems/UnionDropsSystem.h"
#include "Systems/ForceCalculationSystem.h"
#include "Systems/ShiftDropsSystem.h"
#include "Systems/ComplexCollision_InitSystem.h"
#include "Systems/ComplexCollisionSystem.h"
#include "BackGround_InitSystem.h"
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
#include <MenuSystem.h>
#include <iostream>
#endif

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 900

using namespace sf;

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

	auto window = sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ZhiZha",
			sf::Style::Close | sf::Style::Titlebar, settings);

	std::ostream::sync_with_stdio(false);
	gladLoadGL();

	sf::Vector2f gravity = { 0, G / 20 };
	sf::Vector2f camera_location = { 0.0f, 0.0f };
	float global_phi = 0;
	std::vector views = {
			window.getDefaultView(),  // background view
			window.getDefaultView(), // game view
			window.getDefaultView(), // gui view
	};

	auto engine = new Engine(window);
	engine->RegisterSystem<BackGround_InitSystem>(engine->GetResourceManager())
		.RegisterSystem<MenuSystem>(*engine, window).BindToScene(Scene::Menu).UnbindFromScene(Scene::Main)
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
		.RegisterSystem<ComplexCollision_InitSystem>()
		.RegisterSystem<MaterialAttachSystem>(window)

		.RegisterSystem<EventSystem>(window, views[Game], *engine).BindStatic()
		.RegisterSystem<FPSSystem>(engine->GetTime(), engine->GetResourceManager()).BindStatic()
		.RegisterSystem<RenderSystem>(window, views, camera_location, global_phi).BindStatic()
		.RegisterSystem<ButtonClickSystem>(window).BindStatic()

		.RegisterSystem<RotateSystem>(views[Game], gravity, engine->GetTime(), global_phi)
		.RegisterSystem<CollisionSystem>()
		.RegisterSystem<UnionDropsSystem>(window)
		.RegisterSystem<FormZhizhaVolume_System>()
		.RegisterSystem<GravitationSystem>(engine->GetTime(), gravity)
		.RegisterSystem<ForceCalculationSystem>(engine->GetTime(), gravity)
		.RegisterSystem<ShiftDropsSystem>(engine->GetTime(), gravity)
//		.RegisterSystem<ComplexCollisionSystem>()
		.RegisterSystem<ResetParamsSystem>(camera_location)
		.RegisterSystem<CameraMovingSystem>(camera_location);

	engine->LoadScene(Scene::Menu);
	engine->Start();
}
