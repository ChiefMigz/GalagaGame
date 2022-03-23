#ifndef GAME_H
#define GAME_H
#include <SDL/SDL.h>

struct Vector2
{
	float x, y;
};

class Game
{
public:
	//defined externally
	Game(); //should be always public
	bool Initialize(); //we need this to start
	void RunLoop(); //Makes a never ending loop, unless user exits
	void ShutDown(); //closes the program
private:
	//function are normally used internally
	void ProcessInput(); //to read the value or key entered by user
	void UpdateGame(); //updates stuff in game
	void GenerateOutput(); //shows message to user
	//m window means a member of the class
	SDL_Window* mWindow; 
	bool mIsRunning;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
};
#endif