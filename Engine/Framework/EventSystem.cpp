#include "EventSystem.h"

namespace nh
{
	void EventSystem::Startup()
	{

	}

	void EventSystem::Shutdown()
	{

	}

	void EventSystem::Update(float dt)
	{
		
	}

	void EventSystem::Subscribe(const std::string& name, function_t fn)
	{
		observers[name].push_back({ fn });
	}

	void EventSystem::Notify(const Event& e)
	{
		auto& eventObservers = observers[e.name];

		for (const auto& o : eventObservers)
		{
			o.fn(e);
		}
	}
}