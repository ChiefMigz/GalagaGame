#ifndef PLAYER_H
#define PLAYER_H
#include "Vector2.h"
#include "Game.h"

class Player
{
public:
	Player();
	void takeDamage();
	 
private:
	int health;
	int velocity;
	Vector2 position;
};
#endif //PLAYER_H

