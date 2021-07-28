#include "Enemy.h"

#include "Math\MathUtils.h"
#include "Projectile.h"
#include "Engine.h"
#include "Player.h"

void Enemy::Update(float dt)
{
	transform.position += nh::Vector2::Rotate(nh::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = nh::Wrap(transform.position.x, -100.0f, 900.0f);
	transform.position.y = nh::Wrap(transform.position.y, -100.0f, 700.0f);

	Actor::Update(dt);
}

void Enemy::OnCollision(Actor* actor)
{
	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Player")
	{
		actor->destroy = true;

		scene->engine->Get<nh::ParticleSystem>()->Create(transform.position, 200, 2.0f, nh::Color::white, 50.0f);
		scene->engine->Get<nh::AudioSystem>()->PlayAudio("explosion");
		nh::Event e1{ "AddPoints", 100 * size };
		nh::Event e2{ "EnemyHit", this };
		scene->engine->Get<nh::EventSystem>()->Notify(e1);
		scene->engine->Get<nh::EventSystem>()->Notify(e2);
	}
}
