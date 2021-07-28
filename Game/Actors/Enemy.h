#pragma once

#include "Base\Actor.h"

class Enemy : public nh::Actor
{
public:
	Enemy(const nh::Transform& transform, std::shared_ptr<nh::Shape> shape, float speed) : nh::Actor{ transform, shape }, speed{ speed }{}

	void Update(float dt) override;

	virtual void OnCollision(Actor* actor);

private:
	float fireTimer{ 0.0f };
	float fireRate{ 1.0f };
	float speed{ 200.0f };
};