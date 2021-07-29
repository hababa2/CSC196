#include "Player.h"

#include "Projectile.h"
#include "Enemy.h"
#include "Engine.h"
#include "Math\MathUtils.h"
#include <memory>

Player::Player(const nh::Transform& transform, std::shared_ptr<nh::Shape> shape, float speed) : nh::Actor{ transform, shape }, speed{ speed }
{
	std::unique_ptr locator = std::make_unique<Actor>();
	locator->transform.lPosition = { 5.0f, 0.0f };
	locator->transform.lScale = 0.5f;
	AddChild(std::move(locator));
}

void Player::Initialize()
{

}

void Player::Update(float dt)
{
	transform.rotation += (Core::Input::IsPressed('D') - Core::Input::IsPressed('A')) * turnSpeed * dt;
	float thrust = (Core::Input::IsPressed('W') - Core::Input::IsPressed('S')) * speed;

	nh::Vector2 acceleration = nh::Vector2::Rotate(nh::Vector2::right, transform.rotation) * thrust;
	velocity += acceleration * dt;
	transform.position += velocity * dt;

	velocity *= 0.975f;

	transform.position.x = nh::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nh::Wrap(transform.position.y, 0.0f, 600.0f);

	Actor::Update(dt);

	if (((fireTimer -= dt) <= 0) && Core::Input::IsPressed(VK_SPACE))
	{
		scene->engine->Get<nh::AudioSystem>()->PlayAudio("shoot");
		fireTimer = fireRate;
		nh::Transform t = children[0]->transform;
		t.scale = 0.5f;
		std::unique_ptr<Projectile> p = std::make_unique<Projectile>(t,
			scene->engine->Get<nh::ResourceSystem>()->get<nh::Shape>("player.txt"), 600.0f);
		p->tag = "Player";
		scene->AddActor(std::move(p));
	}

	scene->engine->Get<nh::ParticleSystem>()->Create(transform.position, 3, 2.0f, { nh::Color::red }, 50.0f, nh::Pi + transform.rotation, nh::DegToRad(15.0f));
}

void Player::OnCollision(Actor* actor)
{
	if (dynamic_cast<Enemy*>(actor) || (dynamic_cast<Projectile*>(actor) && actor->tag == "Enemy"))
	{
		nh::Event e;
		e.name = "PlayerHit";
		scene->engine->Get<nh::EventSystem>()->Notify(e);
	}
}
