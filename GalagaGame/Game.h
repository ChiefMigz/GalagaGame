#ifndef GAME_H
#define GAME_H
#include <SDL/SDL.h>

class Game
{
public:
	Game(); //should be always public
	bool Initialize(); //we need this to start
	void RunLoop(); //Makes a never ending loop
	void ShutDown(); //closes the program
private:
	//function are normally used internally
	void ProcessInput(); //to read the value or key entered by user
	void UpdateGame(); //updates stuff in game
	void GenerateOutput(); //shows message to user
	SDL_Window* mWindow; //m window means a member of the class
	bool mIsRunning;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
};
#endif
