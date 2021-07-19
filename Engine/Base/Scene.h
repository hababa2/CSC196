#pragma once

#include "Object.h"
#include "core.h"

#include <list>
#include <vector>
#include <memory>

namespace nh
{
	class Actor;
	class Engine;

	class Scene : public Object
	{
	public:
		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		void AddActor(std::unique_ptr<Actor> actor);
		void RemoveActor(Actor* actor);
		void RemoveAll();

		template<typename T>
		T* GetActor() const;
		template<typename T>
		std::vector<T*> GetActors() const;

	public:
		Engine* engine{ nullptr };

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

	template<typename T>
	inline std::vector<T*> Scene::GetActors() const
	{
		std::vector<T*> result;

		for (const auto& actor : actors)
		{
			T* t = dynamic_cast<T*>(actor.get());
			if (t) { result.push_back(t); }
		}

		return result;
	}
}