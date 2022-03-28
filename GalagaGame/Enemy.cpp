#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Game* game)
	:GameEntity(game)
	,mRightSpeed(0.0f)
	,mDownSpeed(0.0f)
{
}

void Enemy::UpdateEntity(float deltaTime)
{
	GameEntity::UpdateEntity(deltaTime);
	Vector2 pos = GetPosition();
	pos.x += mRightSpeed * deltaTime;
}