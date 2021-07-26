#include "Projectile.h"

#include "Engine.h"

void Projectile::Update(float dt)
{
	Actor::Update(dt);

	destroy = ((lifetime -= dt) <= 0);

	transform.position += nh::Vector2::Rotate(nh::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = nh::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nh::Wrap(transform.position.y, 0.0f, 600.0f);

	transform.Update();

	std::vector<nh::Color> colors{ nh::Color::white, nh::Color::red, nh::Color::blue };
	scene->engine->Get<nh::ParticleSystem>()->Create(transform.position, 10, 2.0f, nh::Color::red, 1.0f);
}
