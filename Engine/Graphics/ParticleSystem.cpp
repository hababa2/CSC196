#include "ParticleSystem.h"
#include "../Math/Random.h"

namespace nh
{
	void ParticleSystem::Startup()
	{
		particles.resize(1000000);
	}

	void ParticleSystem::Shutdown()
	{
		particles.clear();
	}

	void ParticleSystem::Update(float dt)
	{
		for (Particle& particle : particles)
		{
			if (particle.isActive)
			{
				particle.lifetime -= dt;
				particle.isActive = particle.lifetime > 0;
				particle.prevPosition = particle.position;
				particle.position += particle.velocity * dt;
			}
		}
	}

	void ParticleSystem::Draw(Core::Graphics& graphics)
	{
		for (const Particle& particle : particles)
		{
			if (particle.isActive)
			{
				graphics.SetColor(particle.color);
				graphics.DrawLine(particle.position.x, particle.position.y, particle.prevPosition.x, particle.prevPosition.y);
			}
		}
	}

	void ParticleSystem::Create(const Vector2& position, size_t count, float lifetime, const Color& color, float speed)
	{
		size_t index = 0;
		for (size_t i = 0; i < count; i++)
		{
			for (;index < particles.size(); index++)
			{
				if (!particles[index].isActive)
				{
					particles[index].isActive = true;
					particles[index].lifetime = lifetime;
					particles[index].position = position;
					particles[index].color = color;
					particles[index].velocity = Vector2{ RandomRange(-1, 1), RandomRange(-1, 1) } * (speed * Random());
					index++;
					break;
				}
			}
		}
	}
}