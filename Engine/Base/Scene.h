#pragma once

#include "Object.h"
#include "core.h"

#include <list>
#include <memory>

namespace nh
{
	class Actor;

	class Scene : public Object
	{
	public:
		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		void AddActor(std::unique_ptr<Actor> actor);

		template<typename T>
		T* GetActor() const;

	private:
		std::list<std::unique_ptr<Actor>> actors;
	};

	template<typename T>
	inline T* Scene::GetActor() const
	{
		for (const auto& actor : actors)
		{
			T* t = dynamic_cast<T*>(actor.get());
			if (t) { return t; }
		}

		return nullptr;
	}
}