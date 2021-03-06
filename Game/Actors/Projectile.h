#pragma once

#include "Base\Actor.h"

class Projectile : public nh::Actor
{
public:
	Projectile(const nh::Transform& transform, std::shared_ptr<nh::Shape> shape, float speed) : nh::Actor{ transform, shape }, speed{ speed }{}

	void Update(float dt) override;

private:
	float lifetime{ 2.0f };
	float speed{ 200.0f };
};