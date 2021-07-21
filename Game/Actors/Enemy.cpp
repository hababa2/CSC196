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
		transform.rotation = nh::Lerp(transform.rotation, (p->transform.position - transform.position).Angle(), dt * 2);

		if (((fireTimer -= dt) <= 0))
		{
			fireTimer = fireRate;
			std::vector<nh::Vector2> points = { {-5, -5}, {5, -5}, {0, 8}, {-5, -5} };
			std::shared_ptr<nh::Shape> shape = std::make_shared<nh::Shape>(points, nh::Color::green);
			nh::Transform t = transform;
			t.scale = 0.5f;
			t.rotation += nh::Pi;

			scene->AddActor(std::make_unique<Projectile>(t, shape, 600.0f));
		}
	}

	transform.position += nh::Vector2::Rotate(nh::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = nh::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nh::Wrap(transform.position.y, 0.0f, 600.0f);
}

void Enemy::OnCollision(Actor* actor)
{
	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Player")
	{
		destroy = true;

		scene->engine->Get<nh::ParticleSystem>()->Create(transform.position, 200, 2.0f, nh::Color::red, 50.0f);
		scene->engine->Get<nh::AudioSystem>()->PlayAudio("explosion");
		nh::Event e;
		e.name = "AddPoints";
		e.data = 100;
		scene->engine->Get<nh::EventSystem>()->Notify(e);
	}
}
