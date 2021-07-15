#include "Projectile.h"

#include "Math\MathUtils.h"

void Projectile::Update(float dt)
{
	Actor::Update(dt);

	transform.position += nh::Vector2::Rotate(nh::Vector2::down, transform.rotation) * speed * dt;
	transform.position.x = nh::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nh::Wrap(transform.position.y, 0.0f, 600.0f);
}
