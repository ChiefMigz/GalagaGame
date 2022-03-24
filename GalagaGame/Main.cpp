#include <iostream>
#include <string>
#include "Game.h"
using namespace std;

int main(int argc, char* args[])
{
	Game game;
	bool loadFlagSuccessful = game.Initialize();
	if (loadFlagSuccessful)
		game.RunLoop();
	game.ShutDown();
	return 0;
}
