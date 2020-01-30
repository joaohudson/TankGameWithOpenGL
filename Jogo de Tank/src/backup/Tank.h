#ifndef _TANK_
#define _TANK_

#include "SDL/SDL.h"
#include "Object.h"
#include "EventListener.h"

class Game;

class Tank : public Object, public EventListener
{
	public:
		Tank(int x, int y, int z, Game *game);
		~Tank();
		void draw() const;
		void input(const SDL_Event *events);
		void update();
		void receiveDamage(int damage);

	private:
		int life;
		Game *game;
		void shot(float teta);
		void death();
};

#endif