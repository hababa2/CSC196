#include "Actor.h"

#include "Graphics\Shape.h"

namespace nh
{
	void Actor::Update(float dt)
	{

	}

	void Actor::Draw(Core::Graphics& graphics)
	{
		shape->Draw(graphics, transform);
	}
}