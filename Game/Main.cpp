#include "core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"
#include "Graphics/ParticleSystem.h"

#include <iostream>
#include <vector>

#define HEIGHT 600
#define WIDTH 800

nh::Vector2 position{ 400, 300 };
nh::ParticleSystem particleSystem;
nh::Vector2 psPostiton{ 400, 300 };
std::vector<nh::Vector2> points = { {-5, -5}, {5, -5}, {0, 5}, {-5, -5} };
nh::Shape shape{ points, nh::Color(1, 1, 1) };

std::vector<nh::Vector2> firework = { {390, 595}, {390, 560}, {410, 560}, {410, 595}, {390, 595} };
std::vector<nh::Vector2> projectile = { {-2.5f, -2.5f}, {-2.5f, 2.5f}, {2.5f, 2.5f}, {2.5f, -2.5f}, {-2.5f, -2.5f} };
nh::Vector2 shootPos = { 400, 560 };
nh::Vector2 projPos = { 0, 0 };
float shootTimer = 0;
bool shot = false;
nh::Shape fwShape{ firework, nh::Color(1, 1, 1) };
nh::Shape projShape{ projectile, nh::Color(1, 1, 1) };

float speed = 200.0f;
float time = 0.0f;

bool Update(float dt)
{
	time += dt;
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		projPos = shootPos;
		shootTimer = 1.5f;
		shot = true;

		//int x, y;
		//Core::Input::GetMousePos(x, y);
		//psPostiton.x = static_cast<float>(x);
		//psPostiton.y = static_cast<float>(y);
		//
		//std::vector<nh::Color> colors{ {1, 1, 1}, {1, 0, 0}, {0, 0, 1} };
		//particleSystem.Create(psPostiton, 30, 1.0f, colors[rand() % colors.size()], 50.0f);
	}
	else
	{
		if (shootTimer > 0)
		{
			shootTimer -= dt;
			projPos.y -= dt * speed;
		}

		if (shootTimer <= 0 && shot)
		{
			shot = false;
			std::vector<nh::Color> colors{ {1, 1, 1}, {1, 0, 0}, {0, 0, 1} };
			particleSystem.Create(projPos, 500, 1.5f, colors[0], 50.0f);
			particleSystem.Create(projPos, 500, 1.5f, colors[1], 50.0f);
			particleSystem.Create(projPos, 500, 1.5f, colors[2], 50.0f);
		}
	}


	particleSystem.Update(dt);

	position.x += (Core::Input::IsPressed('D') - Core::Input::IsPressed('A')) * speed * dt;
	position.y += (Core::Input::IsPressed('S') - Core::Input::IsPressed('W')) * speed * dt;

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	float scale = std::sin(time) + 3;

	//shape.Draw(graphics, position, scale);
	fwShape.Draw(graphics, { 0, 0 }, 1);
	if (shootTimer > 0)
	{
		projShape.Draw(graphics, projPos, 1);
	}
	particleSystem.Draw(graphics);
}

int main()
{
	char name[] = "CSC196";
	Core::Init(name, WIDTH, HEIGHT);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	particleSystem.Startup();

	Core::GameLoop();
	Core::Shutdown();

	particleSystem.Shutdown();
}