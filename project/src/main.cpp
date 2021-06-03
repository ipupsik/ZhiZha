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

void show_menu(RenderWindow& window, int* exit_code)
{
	Texture menu_bg, menu_start, menu_exit;

	menu_bg.loadFromFile("../share/background.jpg");
	menu_start.loadFromFile("../share/start_game.jpg");
	menu_exit.loadFromFile("../share/exit.jpg");

	Sprite bg(menu_bg);
	Sprite start(menu_start);
	Sprite exit(menu_exit);

	bg.setPosition(0, 0);
	start.setPosition(330, 300);
	exit.setPosition(380, 400);

	bool menu_alive = true;
	int hovered_note = 0;

	while (menu_alive)
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		start.setColor(Color::White);
		exit.setColor(Color::White);
		hovered_note = 0;

		window.clear(Color::White);

		if (IntRect(330, 300, 306, 107).contains(Mouse::getPosition(window)))
		{
			start.setColor(Color::Blue);
			hovered_note = 1;
		}
		else if (IntRect(380, 400, 128, 107).contains(Mouse::getPosition(window)))
		{
			exit.setColor(Color::Blue);
			hovered_note = 2;
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			switch (hovered_note)
			{
			case 1:
				menu_alive = false;
				*exit_code = 1;
				break;
			case 2:
				window.close();
				menu_alive = false;
				*exit_code = 2;
			default:
				break;
			}
		}

		window.draw(bg);
		window.draw(start);
		window.draw(exit);

		window.display();
	}
}

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

	int exit_code;
	show_menu(window, &exit_code);

	if (exit_code == 2)
	{
		return 0;
	}

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
		.RegisterSystem<ComplexCollision_InitSystem>()
		//.RegisterSystem<ZhizhaVolume_InitSystem>(engine->GetResourceManager())
		.RegisterSystem<ComplexCollision_InitSystem>()

		.RegisterSystem<MaterialAttachSystem>(window)
		.RegisterSystem<RotateSystem>(views[Game], gravity, engine->GetTime(), global_phi)
		.RegisterSystem<EventSystem>(window, views[Game])
		.RegisterSystem<FPSSystem>(engine->GetTime(), engine->GetResourceManager())

		//.RegisterSystem<FormZhizhaVolume_System>()
		.RegisterSystem<RenderSystem_Models>(window, views, camera_location, global_phi)
		.RegisterSystem<RenderSystem_HUD>(window, views)
		//.RegisterSystem<ZhizhaDraw_System>(window, views, camera_location, global_phi)

		.RegisterSystem<CollisionSystem>()
		.RegisterSystem<UnionDropsSystem>(window)
		.RegisterSystem<FormZhizhaVolume_System>()
		.RegisterSystem<GravitationSystem>(engine->GetTime(), gravity)
		.RegisterSystem<ForceCalculationSystem>(engine->GetTime(), gravity)
		//.RegisterSystem<ComplexCollisionSystem>()
		.RegisterSystem<ShiftDropsSystem>(engine->GetTime(), gravity)
		.RegisterSystem<ResetParamsSystem>(camera_location)
		.RegisterSystem<CameraMovingSystem>(camera_location);
//		.RegisterSystem<EndSystem>(engine->GetTime());
	engine->Start();
}
