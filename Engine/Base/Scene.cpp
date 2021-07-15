#include "Scene.h"

#include "Actor.h"

namespace nh
{
	void Scene::Update(float dt)
	{
		for (const auto& actor : actors)
		{
			actor->Update(dt);
		}
	}

	void Scene::Draw(Core::Graphics& graphics)
	{
		for (const auto& actor : actors)
		{
			actor->Draw(graphics);
		}
	}

	void Scene::AddActor(std::unique_ptr<Actor> actor)
	{
		actor->scene = this;
		actors.push_back(std::move(actor));
	}
}