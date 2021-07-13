#include "core.h"
#include "Graphics/Shape.h"
#include "Engine.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"

#include <iostream>
#include <vector>
#include <string>

#define HEIGHT 600
#define WIDTH 800
#define FRAMERATE 120

nh::Vector2 psPostiton;
std::vector<nh::Vector2> points = { {-5, -5}, {5, -5}, {0, 8}, {-5, -5} };
nh::Shape shape{ points, {1, 1, 1} };
nh::Transform transform{ { 400, 300 }, 0.0f, 3.0f };
float turnSpeed = 3;

float speed = 200.0f;
float time = 0.0f;
float deltaTime;
float gameTime = 0;
bool released = true;

nh::Engine engine;

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

	float thrust = 0;
	transform.rotation += (Core::Input::IsPressed('D') - Core::Input::IsPressed('A')) * turnSpeed * dt;
	thrust = Core::Input::IsPressed('W') * speed;

	transform.position += nh::Vector2::Rotate(nh::Vector2::down, transform.rotation) * thrust * dt;
	transform.position.x = nh::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nh::Wrap(transform.position.y, 0.0f, 600.0f);

	engine.Get<nh::ParticleSystem>()->Create(transform.position, 3, 2.0f, nh::Color::red, 50.0f);
	engine.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	shape.Draw(graphics, transform);
	engine.Get<nh::ParticleSystem>()->Draw(graphics);

	nh::Color color = nh::Lerp(nh::Color::green, nh::Color::blue, psPostiton.x / 800.0f);
	graphics.SetColor(color);

	graphics.DrawString(10, 10, std::to_string(deltaTime).c_str());
	graphics.DrawString(10, 20, std::to_string(gameTime).c_str());
	graphics.DrawString(10, 30, std::to_string(1 / deltaTime).c_str());
	graphics.DrawString(10, 40, std::to_string(psPostiton.Length()).c_str());
}

int main()
{
	char name[] = "CSC196";
	Core::Init(name, WIDTH, HEIGHT, FRAMERATE);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	engine.Startup();
	engine.Get<nh::AudioSystem>()->AddAudio("explosion", "explosion.wav");

	Core::GameLoop();
	Core::Shutdown();

	engine.Shutdown();
}