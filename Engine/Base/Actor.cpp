#include "Actor.h"

#include "Graphics\Shape.h"

namespace nh
{
	void Actor::Draw(Core::Graphics& graphics)
	{
		shape->Draw(graphics, transform);
	}

	float Actor::GetRadius()
	{
		return shape->radius * transform.scale;
	}
}