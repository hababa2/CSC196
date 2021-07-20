#pragma once

#include "Engine.h"

class Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver,
	};

public:
	void Initialize();
	void Shutdown();

	void Update(float dt);
	void Draw(Core::Graphics& graphics);

private:
	void UpdateTitle(float dt);
	void UpdateStartLevel(float dt);
	void UpdateGame(float dt);
	void OnAddPoints(const nh::Event& e);
	void OnPlayerDead(const nh::Event& e);

public:
	std::unique_ptr<nh::Scene> scene;
	std::unique_ptr<nh::Engine> engine;

private:
	eState state = eState::Title;
	float stateTimer = 0.0f;

	void (Game::* stateFn)(float) = nullptr;

	unsigned int score = 0;
	unsigned char lives = 0;
};

