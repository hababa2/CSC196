#pragma once

#include "Base/System.h"
#include <fmod.hpp>
#include <string>
#include <map>

namespace nh
{
	class AudioSystem : public System
	{
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);

		void AddAudio(const std::string& name, const std::string& filename);
		void PlayAudio(const std::string& name);

	private:
		FMOD::System* fmodSystem;
		std::map<std::string, FMOD::Sound*> sounds;
	};
}

extern nh::AudioSystem audioSystem;