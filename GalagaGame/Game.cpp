#include "Game.h"
#include <iostream>
const int HEIGHT = 600;
const int WIDTH = 800;
const int THICKNESS = 15;
const int PADDLE_H = 100;
const float paddleSpeed = 300.0f;

//create constructor
Game::Game()
{
	mWindow = nullptr;
	mIsRunning = true;
	mPaddleDir = 0;
	mTicksCount = 0;
	mColor = 1;
}

bool Game::Initialize()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	mWindow = SDL_CreateWindow("CMPT-1267", 100, 100, 800, 600, 0);
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
	mPaddlePos.x = 10.0f;
	mPaddlePos.y = HEIGHT / 2.0f;
	mBallPos.x = WIDTH / 2.0f;
	mBallPos.y = HEIGHT / 2.0f;

	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;

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
	const Uint8* state = SDL_GetKeyboardState(NULL);

	mPaddleDir = 0;

	if (state[SDL_SCANCODE_ESCAPE])
		mIsRunning = false;
	else if (state[SDL_SCANCODE_W])
		mPaddleDir -= 1;
	else if (state[SDL_SCANCODE_S])
		mPaddleDir += 1;
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

	// Update paddle position based on direction
	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * paddleSpeed * deltaTime;
		// Make sure paddle doesn't move off screen!
		if (mPaddlePos.y < (THICKNESS + PADDLE_H / 2.0f))
			mPaddlePos.y = THICKNESS + PADDLE_H / 2.0f;
		else if (mPaddlePos.y > (HEIGHT - THICKNESS - PADDLE_H / 2.0f ))
			mPaddlePos.y = HEIGHT - PADDLE_H / 2.0f - THICKNESS;
	}

	// Update ball position based on ball velocity
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	// Bounce if needed
	// Did we intersect with the paddle?
	float diff = mPaddlePos.y - mBallPos.y;
	// Take absolute value of difference
	diff = (diff > 0.0f) ? diff : -diff;
	if (
		// Our y-difference is small enough
		diff <= PADDLE_H / 2.0f &&
		// We are in the correct x-position
		mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
		// The ball is moving to the left
		mBallVel.x < 0.0f)
	{
		mBallVel.x *= -1.0f;
		changeColor();
	}
	// Did the ball go off the screen? (if so, end game)
	else if (mBallPos.x <= 0.0f)
	{
		mIsRunning = false;
	}
	// Did the ball collide with the right wall?
	else if (mBallPos.x >= (WIDTH - THICKNESS) && mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1.0f;
	}

	// Did the ball collide with the top wall?
	if (mBallPos.y <= THICKNESS && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1;
	}
	// Did the ball collide with the bottom wall?
	else if (mBallPos.y >= (HEIGHT - THICKNESS) &&
		mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1;
	}
}

void Game::changeColor()
{
	if (mColor != 3)
		mColor++;
	else
		mColor = 1;
}

void Game::renderColor()
{
	if (mColor == 1) // Blue
	{
		SDL_SetRenderDrawColor(
			mRenderer,
			0,		// R
			0,		// G 
			255,	// B
			255		// A
		);
	}

	else if (mColor == 2) //green
	{
		SDL_SetRenderDrawColor(
			mRenderer,
			0,		// R
			255,	// G 
			0,		// B
			255		// A
		);
	}
	else if (mColor == 3) //purple
	{
		SDL_SetRenderDrawColor(
			mRenderer,
			255,	// R
			0,		// G 
			255,	// B
			255		// A
		);
	}
}

void Game::GenerateOutput()
{
	// Set draw color to blue
	renderColor();
	
	// Clear back buffer
	SDL_RenderClear(mRenderer);

	// Draw walls
	SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);

	// Draw top wall
	SDL_Rect wall {
		0,			// Top left x
		0,			// Top left y
		WIDTH,		// Width
		THICKNESS	// Height
	};
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw bottom wall
	wall.y = HEIGHT - THICKNESS;
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw right wall
	wall.x = WIDTH - THICKNESS;
	wall.y = 0;
	wall.w = THICKNESS;
	wall.h = HEIGHT;
	SDL_RenderFillRect(mRenderer, &wall);

	SDL_Rect ball{ mBallPos.x - THICKNESS / 2, mBallPos.y - THICKNESS / 2, THICKNESS, THICKNESS };
	SDL_RenderFillRect(mRenderer, &ball);

	SDL_Rect paddle{ mPaddlePos.x - THICKNESS / 2, mPaddlePos.y - PADDLE_H / 2, THICKNESS, PADDLE_H };
	SDL_RenderFillRect(mRenderer, &paddle);

	

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

