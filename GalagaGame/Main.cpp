#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <iostream>
#include <string>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main(int argc, char* args[])
{
	Game game;
	bool loadFlagSuccessful = game.Initialize();
	if (loadFlagSuccessful)
		game.runLoop();
	game.ShutDown();
	return 0;
}
