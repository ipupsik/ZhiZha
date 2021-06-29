#include "Systems/RenderSystem_HUD.h"
#include "Systems/RenderSystem_Models.h"
#include "Systems/MoveSystem.h"
#include "Systems/EndSystem.h"
#include "DefinesPhysics.h"
#include "Zhizha_InitSystem.h"
#include "Map_InitSystem.h"
#include "Engine.h"
#include "Components/LayerComponent.h"
#include "glad/glad.h"

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
//#include "Systems/TestSystem.h"
#include "BackGround_InitSystem.h"

#include "ZhizhaDraw_System.h"
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
#include "Systems/ComplexCollision_InitSystem.h"

#if defined(linux)
#include <X11/Xlib.h>
#endif

#define OK 0
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

	gladLoadGL();

	sf::Vector2f gravity = { 0, G / 20 };
	sf::Vector2f camera_location = { 0.0f, 0.0f };
	float global_phi = 0;
	std::vector views = {
			window.getDefaultView(), // game view
			window.getDefaultView() // gui view
	};

	views.at(Game).zoom(3);

	auto engine = new Engine(window);
	engine->RegisterSystem<Map_InitSystem>(engine->GetResourceManager())
		.RegisterSystem<MaterialAttachSystem>(window)
		.RegisterSystem<RotateSystem>(views[Game], gravity, engine->GetTime(), global_phi)
		.RegisterSystem<EventSystem>(window, views[Game])
		.RegisterSystem<RenderSystem_Models>(window, views, camera_location, global_phi)
		.RegisterSystem<RenderSystem_HUD>(window, views);

	engine->Start();
}
