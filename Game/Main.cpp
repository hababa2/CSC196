#include "Game.h"


#define HEIGHT 600
#define WIDTH 800
#define FRAMERATE 120

Game game;

bool Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	game.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	game.Draw(graphics);
}

#include "Math\Matrix2.h"

int main()
{
	char name[] = "CSC196";
	Core::Init(name, WIDTH, HEIGHT, FRAMERATE);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	game.Initialize();

	Core::GameLoop();
	Core::Shutdown();

	game.Shutdown();
}