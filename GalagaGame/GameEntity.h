#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <vector>
#include "Math.h"

class GameEntity
{
public:
    enum EntityState
    {
        EActive,
        EDead
    };

    GameEntity(class Game* game);
    virtual ~GameEntity();

    //call this function in Game.cpp
    void update(float deltaTime);
    //update for specific actors
    virtual void updateEntity(float delayTime);

    //accessors and mutators
    const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	EntityState GetState() const { return mState; }
	void SetState(EntityState state) { mState = state; }

	class Game* GetGame() { return mGame; }
private:
    EntityState mState;

	// Transform
	Vector2 mPosition;
	float mScale;
	float mRotation;

	class Game* mGame;

};

#endif
