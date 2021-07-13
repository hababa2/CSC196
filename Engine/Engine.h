#pragma once

#include "Graphics\ParticleSystem.h"
#include "Audio\AudioSystem.h"

#include <vector>
#include <memory>

namespace nh
{
	class Engine
	{
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);

		template<typename T>
		T* Get();

	private:
		std::vector<std::unique_ptr<System>> systems;
	};

	template<typename T>
	inline T* Engine::Get()
	{
		for (auto& system : systems)
		{
			T* t = dynamic_cast<T*>(system.get());
			if (t) { return t; }
		}

		return nullptr;
	}
}