#include "Player.h"

#include "Projectile.h"
#include "Engine.h"
#include "Math\MathUtils.h"
#include <memory>

void Player::Update(float dt)
{
	Actor::Update(dt);

	float thrust = 0;
	transform.rotation += (Core::Input::IsPressed('D') - Core::Input::IsPressed('A')) * turnSpeed * dt;
	thrust = (Core::Input::IsPressed('W') - Core::Input::IsPressed('S')) * speed;

	transform.position += nh::Vector2::Rotate(nh::Vector2::down, transform.rotation) * thrust * dt;
	transform.position.x = nh::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nh::Wrap(transform.position.y, 0.0f, 600.0f);

	if (Core::Input::IsPressed(VK_SPACE))
	{
		std::vector<nh::Vector2> points = { {-5, -5}, {5, -5}, {0, 8}, {-5, -5} };
		std::shared_ptr<nh::Shape> shape = std::make_shared<nh::Shape>(points, nh::Color::green);
		nh::Transform t = transform;
		t.scale = 0.5f;

		scene->AddActor(std::make_unique<Projectile>(t, shape, 600.0f));
	}
}
