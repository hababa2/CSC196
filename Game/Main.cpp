#include "core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"
#include "Graphics/ParticleSystem.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"

#include <iostream>
#include <vector>
#include <string>

#define HEIGHT 600
#define WIDTH 800
#define FRAMERATE 120

nh::ParticleSystem particleSystem;
nh::Vector2 psPostiton{ 400, 300 };
std::vector<nh::Vector2> points = { {-5, -5}, {5, -5}, {0, 8}, {-5, -5} };
nh::Shape shape{ points, {1, 1, 1} };
nh::Transform transform{ { 400, 300 }, 0.0f, 3.0f };
float turnSpeed = 3;

//std::vector<nh::Vector2> firework = { {390, 595}, {390, 560}, {410, 560}, {410, 595}, {390, 595} };
//std::vector<nh::Vector2> projectile = { {-2.5f, -2.5f}, {-2.5f, 2.5f}, {2.5f, 2.5f}, {2.5f, -2.5f}, {-2.5f, -2.5f} };
//nh::Vector2 shootPos = { 400, 560 };
//nh::Vector2 projPos = { 0, 0 };
//float shootTimer = 0;
//bool shot = false;
//nh::Shape fwShape{ firework, nh::Color::white };
//nh::Shape projShape{ projectile, nh::Color::white };

float speed = 200.0f;
float time = 0.0f;
float deltaTime;
float gameTime = 0;

bool Update(float dt)
{
	deltaTime = dt;
	gameTime += dt;
	time += dt;
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		//projPos = shootPos;
		//shootTimer = 1.5f;
		//shot = true;

		int x, y;
		Core::Input::GetMousePos(x, y);
		psPostiton.x = static_cast<float>(x);
		psPostiton.y = static_cast<float>(y);
		
		std::vector<nh::Color> colors{ nh::Color::white, nh::Color::red, nh::Color::blue };
		particleSystem.Create(psPostiton, 30, 1.0f, colors[nh::RandomRangeInt(0, colors.size())], 50.0f);
	}
	//else
	//{
	//	if (shootTimer > 0)
	//	{
	//		shootTimer -= dt;
	//		projPos.y -= dt * speed;
	//	}
	//
	//	if (shootTimer <= 0 && shot)
	//	{
	//		shot = false;
	//		std::vector<nh::Color> colors{ nh::Color::white, nh::Color::red, nh::Color::blue };
	//		particleSystem.Create(projPos, 500, 1.5f, colors[0], 50.0f);
	//		particleSystem.Create(projPos, 500, 1.5f, colors[1], 50.0f);
	//		particleSystem.Create(projPos, 500, 1.5f, colors[2], 50.0f);
	//	}
	//}

	particleSystem.Update(dt);

	float thrust = 0;
	transform.rotation += (Core::Input::IsPressed('D') - Core::Input::IsPressed('A')) * turnSpeed * dt;
	thrust = Core::Input::IsPressed('W') * speed;

	transform.position += nh::Vector2::Rotate(nh::Vector2::down, transform.rotation) * thrust * dt;
	transform.position.x = nh::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nh::Wrap(transform.position.y, 0.0f, 600.0f);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	shape.Draw(graphics, transform);
	//fwShape.Draw(graphics, { 0, 0 }, 1);
	//if (shootTimer > 0)
	//{
	//	projShape.Draw(graphics, projPos, 1);
	//}
	particleSystem.Draw(graphics);

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

	particleSystem.Startup();

	Core::GameLoop();
	Core::Shutdown();

	particleSystem.Shutdown();
}