#include "Enemy.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Enemy::Enemy(Game* game)
	:Actor(game)
	, mRightSpeed(0.0f)
	, mDownSpeed(0.0f)
{
	// Create an animated sprite component
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Enemy01.png"),
		game->GetTexture("Assets/Enemy02.png"),
		game->GetTexture("Assets/Enemy03.png"),
		game->GetTexture("Assets/Enemy04.png"),
	};
	asc->SetAnimTextures(anims);
	//mCurrentPath = path;
}

void Enemy::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// Update position based on speeds and delta time
	Vector2 pos = GetPosition();
	pos.x += mRightSpeed * deltaTime;
	pos.y += mDownSpeed * deltaTime;

	SetPosition(pos);
}

//void Enemy::createPaths()
//{
//	int currentPath = 0;
//	BezierPath* path = new BezierPath();
//	path->addCurve({ Vector2(500.0f, 10.0f), Vector2(500.0f, 0.0f), Vector2(500.0f, 300.0f) }, 1);
//
//
//	sPaths.push_back(std::vector<Vector2>());
//	path->sample(&sPaths[currentPath]);
//	delete path;
//
//}



