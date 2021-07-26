#include "Player.h"

#include "Projectile.h"
#include "Enemy.h"
#include "Engine.h"
#include "Math\MathUtils.h"
#include <memory>

void Player::Update(float dt)
{
	Actor::Update(dt);

	float thrust = 0;
	transform.rotation += (Core::Input::IsPressed('D') - Core::Input::IsPressed('A')) * turnSpeed * dt;
	thrust = (Core::Input::IsPressed('W') - Core::Input::IsPressed('S')) * speed;

	transform.position += nh::Vector2::Rotate(nh::Vector2::right, transform.rotation) * thrust * dt;
	transform.position.x = nh::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nh::Wrap(transform.position.y, 0.0f, 600.0f);

	transform.Update();

	if (((fireTimer -= dt) <= 0) && Core::Input::IsPressed(VK_SPACE))
	{
		fireTimer = fireRate;
		nh::Transform t = transform;
		t.scale = 0.5f;
		std::unique_ptr<Projectile> p = std::make_unique<Projectile>(t, 
			scene->engine->Get<nh::ResourceSystem>()->get<nh::Shape>("player.txt"), 600.0f);
		p->tag = "Player";
		scene->AddActor(std::move(p));
	}

	scene->engine->Get<nh::ParticleSystem>()->Create(transform.position, 3, 2.0f, nh::Color::red, 50.0f);
}

void Player::OnCollision(Actor* actor)
{
	if (dynamic_cast<Enemy*>(actor))
	{
		scene->engine->Get<nh::ParticleSystem>()->Create(transform.position, 200, 2.0f, nh::Color::red, 50.0f);
		scene->engine->Get<nh::AudioSystem>()->PlayAudio("explosion");
		nh::Event e;
		e.name = "PlayerHit";
		e.data = std::string("I'm dead");
		scene->engine->Get<nh::EventSystem>()->Notify(e);
	}
}
