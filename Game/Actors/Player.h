#pragma once

#include "Base\Actor.h"

class Player : public nh::Actor
{
public:
	Player(const nh::Transform& transform, std::shared_ptr<nh::Shape> shape, float speed);

	void Update(float dt) override;
	virtual void OnCollision(Actor* actor);

private:
	float fireTimer{ 0.0f };
	float fireRate{ 0.4f };
	float turnSpeed{ 3.0f };
	float speed{ 200.0f };
};