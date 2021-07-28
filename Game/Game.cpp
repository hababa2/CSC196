#include "Game.h"

#include "Actors\Player.h"
#include "Actors\Enemy.h"

void Game::Initialize()
{
	engine = std::make_unique<nh::Engine>();
	engine->Startup();

	scene = std::make_unique<nh::Scene>();
	scene->engine = engine.get();

	engine->Get<nh::AudioSystem>()->AddAudio("explosion", "explosion.wav");

	state = eState::Title;

	engine->Get<nh::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<nh::EventSystem>()->Subscribe("PlayerHit", std::bind(&Game::OnPlayerHit, this, std::placeholders::_1));
	engine->Get<nh::EventSystem>()->Subscribe("EnemyHit", std::bind(&Game::OnEnemyHit, this, std::placeholders::_1));
}

void Game::Shutdown()
{
	scene->RemoveAll();
	engine->Shutdown();
}

void Game::Update(float dt)
{
	stateTimer += dt;

	switch (state)
	{
	case Game::eState::Title:
		UpdateTitle(dt);
		break;
	case Game::eState::StartGame:
		score = 0;
		lives = 3;
		state = eState::StartLevel;
		break;
	case Game::eState::StartLevel:
		UpdateStartLevel(dt);
		break;
	case Game::eState::Game:
		UpdateGame(dt);
		break;
	case Game::eState::GameOver:
		if (Core::Input::IsPressed(VK_SPACE)) { state = eState::StartGame; }
		break;
	default:
		break;
	}

	engine->Update(dt);
	scene->Update(dt);
}

void Game::Draw(Core::Graphics& graphics)
{
	switch (state)
	{
	case Game::eState::Title:
		graphics.SetColor(nh::Color::blue);
		graphics.DrawString(380, 300 + static_cast<int>(std::sin(stateTimer * 3.0f) * 4.0f), "MY GAME");
		graphics.DrawString(340, 400, "PRESS SPACE TO START");
		break;
	case Game::eState::StartGame:
		break;
	case Game::eState::StartLevel:
		break;
	case Game::eState::Game:
		break;
	case Game::eState::GameOver:
		graphics.SetColor(nh::Color::red);
		graphics.DrawString(380, 300 + static_cast<int>(std::sin(stateTimer * 3.0f) * 4.0f), "GAME OVER");
		graphics.DrawString(340, 400, "PRESS SPACE TO RESTART");
		break;
	default:
		break;
	}

	graphics.SetColor(nh::Color::white);
	graphics.DrawString(30, 20, std::to_string(score).c_str());
	graphics.DrawString(750, 20, std::to_string(lives).c_str());

	scene->Draw(graphics);
	engine->Draw(graphics);
}

void Game::UpdateTitle(float dt)
{
	if (Core::Input::IsPressed(VK_SPACE)) { state = eState::StartGame; }
}

void Game::UpdateStartLevel(float dt)
{
	scene->RemoveAll();

	scene->AddActor(std::make_unique<Player>(nh::Transform{ { 400, 300 }, 0.0f, 3.0f }, 
		engine->Get<nh::ResourceSystem>()->get<nh::Shape>("player.txt"), 200.0f));

	for (size_t i = 0; i < 10; i++)
	{
		scene->AddActor(std::make_unique<Enemy>(nh::Transform{ { nh::RandomRange(-100.0f, 900.0f), nh::RandomRange(-100.0f, 700.0f) },
			nh::RandomRange(0.0f, nh::TwoPi), 6.0f },
			engine->Get<nh::ResourceSystem>()->get<nh::Shape>("asteroid1.txt"), nh::RandomRange(10.0f, 100.0f)));
	}

	state = eState::Game;
}

void Game::UpdateGame(float dt)
{
	iFrameCounter -= dt;

	if ((spawnerTimer -= dt) <= 0.0f)
	{
		spawnerTimer = 5.0f;

		scene->AddActor(std::make_unique<Enemy>(nh::Transform{ { nh::RandomRange(-100.0f, 900.0f), nh::RandomRange(-100.0f, 700.0f) },
			nh::RandomRange(0.0f, nh::TwoPi), 6.0f },
			engine->Get<nh::ResourceSystem>()->get<nh::Shape>("asteroid1.txt"), nh::RandomRange(10.0f, 100.0f)));
	}
}

void Game::OnAddPoints(const nh::Event& e)
{
	score += std::get<int>(e.data);
}

void Game::OnPlayerHit(const nh::Event& e)
{
	if (iFrameCounter <= 0.0f)
	{
		iFrameCounter = 0.5f;
		if (--lives == 0)
		{
			state = eState::GameOver;
			scene->GetActor<Player>()->destroy = true;
		}
	}
}

void Game::OnEnemyHit(const nh::Event& e)
{
	Enemy* enemy = dynamic_cast<Enemy*>(std::get<nh::Actor*>(e.data));
	enemy->destroy = true;

	enemy->size--;

	if (enemy->size > 0)
	{
		nh::Transform t = enemy->transform;
		t.rotation = nh::RandomRange(0.0f, nh::TwoPi);
		t.scale = enemy->size * 2.0f;

		for (int i = 0; i < 2; ++i)
		{
			std::unique_ptr newEnemy = std::make_unique<Enemy>(t, 
				engine->Get<nh::ResourceSystem>()->get<nh::Shape>("asteroid1.txt"), nh::RandomRange(30.0f, 100.0f));
			newEnemy->size = enemy->size;
			scene->AddActor(std::move(newEnemy));
			t.rotation = nh::RandomRange(0.0f, nh::TwoPi);
		}
	}
}
