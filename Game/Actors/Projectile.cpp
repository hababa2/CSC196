#include "Projectile.h"

#include "Engine.h"

void Projectile::Update(float dt)
{
	transform.position += nh::Vector2::Rotate(nh::Vector2::right, transform.rotation) * speed * dt;
	destroy |= ((lifetime -= dt) <= 0) || (transform.position.x > 900.0f || transform.position.x < -100.0f ||
		transform.position.y > 700.0f || transform.position.y < -100.0f);

	Actor::Update(dt);

	std::vector<nh::Color> colors{ nh::Color::white, nh::Color::red, nh::Color::blue };
	scene->engine->Get<nh::ParticleSystem>()->Create(transform.position, 10, 2.0f, nh::Color::red, 1.0f);
}
