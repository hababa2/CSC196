#pragma once

#include "Base\System.h"

#include <string>
#include <functional>
#include <map>
#include <list>

namespace nh
{
	struct Event
	{
		std::string name;
	};

	class EventSystem : public System
	{
	public:
		typedef std::function<void(const Event&)> function_t;

	private:
		struct Observer
		{
			function_t fn;
		};

	public:
		void Startup() override;
		void Shutdown() override;
		void Update(float dt) override;

		void Subscribe(const std::string& name, function_t fn);
		void Notify(const Event& e);

	private:
		std::map<std::string, std::list<Observer>> observers;
	};
}