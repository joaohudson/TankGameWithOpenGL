#include "Tank.h"
#include "Game.h"

#define MAX_LIFE 100

Tank::Tank(int x, int y, int z, Game *game) : Object(x, y, z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->game = game;
	life = MAX_LIFE;
}

Tank::~Tank()
{

}

void Tank::update()
{

}

void Tank::draw() const
{

}

void Tank::input(const SDL_Event *events)
{

}

void Tank::receiveDamage(int damage)
{
	if(damage <= 0)
		return;

	life -= damage;

	if(life <= 0)
	{
		death();
	}
}

void Tank::shot(float teta)
{

}

void Tank::death()
{
	game->removeObject(this);
}