#include "Enemy.h"

#include "Math\MathUtils.h"
#include "Projectile.h"
#include "Engine.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	transform.position += nh::Vector2::Rotate(nh::Vector2::up, transform.rotation) * speed * dt;
	transform.position.x = nh::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nh::Wrap(transform.position.y, 0.0f, 600.0f);
}

void Enemy::OnCollision(Actor* actor)
{
	if (dynamic_cast<Projectile*>(actor))
	{
		destroy = true;

		scene->engine->Get<nh::ParticleSystem>()->Create(transform.position, 200, 2.0f, nh::Color::red, 50.0f);
		scene->engine->Get<nh::AudioSystem>()->PlayAudio("explosion");
	}
}
