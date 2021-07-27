#include "Actor.h"

#include "Graphics\Shape.h"

namespace nh
{
	void Actor::Update(float dt)
	{
		transform.Update();
	}

	void Actor::Draw(Core::Graphics& graphics)
	{
		if (shape)
		{
			shape->Draw(graphics, transform);
		}
	}

	float Actor::GetRadius()
	{
		return shape->radius * transform.scale;
	}
}