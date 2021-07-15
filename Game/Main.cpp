#include "Engine.h"

#include "Actors\Player.h"
#include "Actors\Enemy.h"

#include <iostream>
#include <string>

#define HEIGHT 600
#define WIDTH 800
#define FRAMERATE 120

nh::Vector2 psPostiton;
std::vector<nh::Vector2> points = { {-5, -5}, {5, -5}, {0, 8}, {-5, -5} };

float time = 0.0f;
float deltaTime;
float gameTime = 0;
bool released = true;

nh::Engine engine;
nh::Scene scene;

bool Update(float dt)
{
	deltaTime = dt;
	gameTime += dt;
	time += dt;
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		if (released)
		{
			released = false;
			int x, y;
			Core::Input::GetMousePos(x, y);
			psPostiton.x = static_cast<float>(x);
			psPostiton.y = static_cast<float>(y);

			std::vector<nh::Color> colors{ nh::Color::white, nh::Color::red, nh::Color::blue };
			engine.Get<nh::ParticleSystem>()->Create(psPostiton, 30, 1.0f, colors[nh::RandomRangeInt(0, colors.size())], 50.0f);
			engine.Get<nh::AudioSystem>()->PlayAudio("explosion");
		}
	}
	else
	{
		released = true;
	}

	//engine.Get<nh::ParticleSystem>()->Create(actor.transform.position, 3, 2.0f, nh::Color::red, 50.0f);

	scene.GetActor<Enemy>()->shape->color = nh::Color{ nh::Random(), nh::Random(), nh::Random()};

	scene.Update(dt);
	engine.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	engine.Get<nh::ParticleSystem>()->Draw(graphics);
	scene.Draw(graphics);

	nh::Color color = nh::Lerp(nh::Color::green, nh::Color::blue, psPostiton.x / 800.0f);
	graphics.SetColor(color);

	graphics.DrawString(10, 10, std::to_string(deltaTime).c_str());
	graphics.DrawString(10, 20, std::to_string(gameTime).c_str());
	graphics.DrawString(10, 30, std::to_string(1 / deltaTime).c_str());
	graphics.DrawString(10, 40, std::to_string(psPostiton.Length()).c_str());
}

void Init()
{
	std::shared_ptr<nh::Shape> shape1 = std::make_shared<nh::Shape>(points, nh::Color::green);
	std::shared_ptr<nh::Shape> shape2 = std::make_shared<nh::Shape>(points, nh::Color::red);

	engine.Get<nh::AudioSystem>()->AddAudio("explosion", "explosion.wav");

	scene.AddActor(std::make_unique<Player>( nh::Transform{ { 400, 300 }, 0.0f, 3.0f }, shape1, 200.0f ));
	for (size_t i = 0; i < 100; i++)
	{
		scene.AddActor(std::make_unique<Enemy>( nh::Transform{ { 300, 400 }, nh::RandomRange(0, nh::TwoPi), 2.0f }, shape2, 200.0f ));
	}
}

int main()
{
	char name[] = "CSC196";
	Core::Init(name, WIDTH, HEIGHT, FRAMERATE);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	engine.Startup();
	Init();

	Core::GameLoop();
	Core::Shutdown();

	engine.Shutdown();
}