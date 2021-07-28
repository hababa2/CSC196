#include "Actor.h"

#include "Graphics\Shape.h"

namespace nh
{
	void Actor::Update(float dt)
	{
		transform.Update();

		for (auto& c : children)
		{
			c->transform.Update(transform.matrix);
		}
	}

	void Actor::Draw(Core::Graphics& graphics)
	{
		if (shape)
		{
			shape->Draw(graphics, transform);
		}
	}

	void Actor::AddChild(std::unique_ptr<Actor> a)
	{
		a->parent = this;
		children.push_back(std::move(a));
	}

	float Actor::GetRadius()
	{
		return shape->radius * transform.scale.x;
	}
}