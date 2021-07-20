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
	//stateFn = &Game::UpdateTitle;
}

void Game::Shutdown()
{
	scene->RemoveAll();
	engine->Shutdown();
}

void Game::Update(float dt)
{
	stateTimer += dt;

	//(this->*stateFn)(dt);

	switch (state)
	{
	case Game::eState::Title:
		if (Core::Input::IsPressed(VK_SPACE)) { state = eState::StartGame; }
		break;
	case Game::eState::StartGame:
		score = 0;
		lives = 3;
		state = eState::StartLevel;
		break;
	case Game::eState::StartLevel:
	{
		std::shared_ptr<nh::Shape> player = std::make_shared<nh::Shape>();
		player->Load("player.txt");
		std::shared_ptr<nh::Shape> enemy = std::make_shared<nh::Shape>();
		enemy->Load("enemy.txt");

		scene->AddActor(std::make_unique<Player>(nh::Transform{ { 400, 300 }, 0.0f, 3.0f }, player, 200.0f));
		for (size_t i = 0; i < 100; i++)
		{
			scene->AddActor(std::make_unique<Enemy>(nh::Transform{ { 400, 300 }, nh::RandomRange(0, nh::TwoPi), 2.0f }, enemy, 200.0f));
		}
		state = eState::Game;
	}	break;
	case Game::eState::Game:
		break;
	case Game::eState::GameOver:
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
		break;
	default:
		break;
	}

	graphics.SetColor(nh::Color::white);
	graphics.DrawString(30, 20, std::to_string(score).c_str());
	graphics.DrawString(750, 20, std::to_string(lives).c_str());

	scene->Draw(graphics);
	engine->Get<nh::ParticleSystem>()->Draw(graphics);
}

void Game::UpdateTitle(float dt)
{
	if (Core::Input::IsPressed(VK_SPACE)) { stateFn = &Game::UpdateStartLevel; }
}

void Game::UpdateStartLevel(float dt)
{
	std::shared_ptr<nh::Shape> player = std::make_shared<nh::Shape>();
	player->Load("player.txt");
	std::shared_ptr<nh::Shape> enemy = std::make_shared<nh::Shape>();
	enemy->Load("enemy.txt");

	scene->AddActor(std::make_unique<Player>(nh::Transform{ { 400, 300 }, 0.0f, 3.0f }, player, 200.0f));
	for (size_t i = 0; i < 100; i++)
	{
		scene->AddActor(std::make_unique<Enemy>(nh::Transform{ { 400, 300 }, nh::RandomRange(0, nh::TwoPi), 2.0f }, enemy, 200.0f));
	}

	stateFn = &Game::UpdateGame;
}

void Game::UpdateGame(float dt)
{

}
