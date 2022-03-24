#include <iostream>
#include <string>
#include "Game.h"
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main(int argc, char* args[])
{
	Game game;
	bool loadFlagSuccessful = game.Initialize();
	if (loadFlagSuccessful)
		game.RunLoop();
	game.ShutDown();
	return 0;
}
