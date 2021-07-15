#pragma once

#include "Base\Actor.h"

class Projectile : public nh::Actor
{
public:
	Projectile(const nh::Transform& transform, std::shared_ptr<nh::Shape> shape, float speed) : nh::Actor{ transform, shape }, speed{ speed }{}
	Projectile(const Actor& actor, float speed) : nh::Actor{ actor }, speed{ speed }{}

	void Update(float dt) override;

private:
	float speed{ 200.0f };
};