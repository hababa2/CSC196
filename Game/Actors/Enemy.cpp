#include "Enemy.h"

#include "Math\MathUtils.h"
#include "Projectile.h"
#include "Engine.h"
#include "Player.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	Player* p;
	if (p = scene->GetActor<Player>())
	{
		nh::Vector2 dir = p->transform.position - transform.position;
		nh::Vector2 forward = nh::Vector2::Rotate(nh::Vector2::right, transform.rotation);

		float turnAngle = nh::Vector2::SignedAngle(forward, dir.Normalized());
		transform.rotation = nh::Lerp(transform.rotation, transform.rotation + turnAngle, dt * 3);

		float angle = nh::Vector2::Angle(forward, dir.Normalized());

		fireTimer -= dt;
		if ((fireTimer <= 0) && angle <= nh::DegToRad(10))
		{
			fireTimer = fireRate;
			nh::Transform t = transform;
			t.scale = 0.5f;

			scene->AddActor(std::make_unique<Projectile>(t, 
				scene->engine->Get<nh::ResourceSystem>()->get<nh::Shape>("player.txt"), 600.0f));
		}

		transform.position += nh::Vector2::Rotate(nh::Vector2::right, transform.rotation) * speed * dt;
		transform.position.x = nh::Wrap(transform.position.x, 0.0f, 800.0f);
		transform.position.y = nh::Wrap(transform.position.y, 0.0f, 600.0f);
	}
}

void Enemy::OnCollision(Actor* actor)
{
	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Player")
	{
		destroy = true;
		actor->destroy = true;

		scene->engine->Get<nh::ParticleSystem>()->Create(transform.position, 200, 2.0f, nh::Color::red, 50.0f);
		scene->engine->Get<nh::AudioSystem>()->PlayAudio("explosion");
		nh::Event e;
		e.name = "AddPoints";
		e.data = 100;
		scene->engine->Get<nh::EventSystem>()->Notify(e);
	}
}
