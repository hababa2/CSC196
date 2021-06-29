#include "core.h"

#include <iostream>

#define HEIGHT 600
#define WIDTH 800

bool Update(float dt) 
{ 
	return false; 
}

void Draw(Core::Graphics& graphics) 
{ 
	for (int i = 0; i < 100; i++)
	{
		graphics.SetColor(RGB(rand() % CHAR_MAX, rand() % CHAR_MAX, rand() % CHAR_MAX));
		graphics.DrawLine(static_cast<float>(rand() % WIDTH), static_cast<float>(rand() % HEIGHT),
			static_cast<float>(rand() % WIDTH), static_cast<float>(rand() % HEIGHT));
	}
}

int main()
{
	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}