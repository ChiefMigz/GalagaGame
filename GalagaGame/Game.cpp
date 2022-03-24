#include <iostream>
#include "Game.h"

//create constructor
Game::Game()
{
	mWindow = nullptr;
	mIsRunning = true;
	mTicksCount = 0;
}

bool Game::Initialize()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	mWindow = SDL_CreateWindow("Galaga Game", 100, 100, 800, 600, 0);
	if (!mWindow)
	{
		SDL_Log("Unable to Create Window: %s", SDL_GetError());
		return false;
	}
	//if all successful, return true
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		//Read user activity
		ProcessInput();
		//Update the game regularly
		UpdateGame();
		//Generate message to user
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	
	while (SDL_PollEvent(&event)) //read user activity/input and store it in event
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}
}

void Game::UpdateGame()
{
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 2))
		;

	// Delta time is the difference in ticks from last frame
	// (converted to seconds)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// Clamp maximum delta time value
	if (deltaTime > 0.05f)
		deltaTime = 0.05f;

	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicks();

}

void Game::GenerateOutput()
{
	// Set draw color to black
	SDL_SetRenderDrawColor(
			mRenderer,
			255,	// R
			255,	// G 
			255,	// B
			255	// A
		);
	
	// Clear back buffer
	SDL_RenderClear(mRenderer);

	// Draw walls
	SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);

	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}

void Game::ShutDown()
{
	SDL_DestroyWindow(mWindow);
	mWindow = nullptr;
	SDL_DestroyRenderer(mRenderer);
	mRenderer = nullptr;
	SDL_Quit();
}
