#pragma once

#include "Base\Actor.h"

class Player : public nh::Actor
{
public:
	Player(const nh::Transform& transform, std::shared_ptr<nh::Shape> shape, float speed) : nh::Actor{ transform, shape }, speed{ speed }{}
	Player(const Actor& actor, float speed) : nh::Actor{ actor }, speed{ speed }{}

	void Update(float dt) override;

private:
	float turnSpeed{ 3.0f };
	float speed{ 200.0f };
};