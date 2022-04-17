#pragma once
#include "Actor.h"
#include "BezierPath.h"
class Enemy : public Actor
{
public:
	Enemy(class Game* game);
	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state) = delete;
	float GetRightSpeed() const { return mRightSpeed; }
	float GetDownSpeed() const { return mDownSpeed; }
	static void createPaths();
private:
	float mRightSpeed;
	float mDownSpeed;

	static std::vector<std::vector<Vector2>> sPaths;
	int mCurrentPath;
	int mCurrentWaypoint;
	const float EPSILON = 5.0f;
};

