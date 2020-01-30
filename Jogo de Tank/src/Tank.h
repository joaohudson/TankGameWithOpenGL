#ifndef _TANK_
#define _TANK_

#include "SDL/SDL.h"
#include "Object.h"
#include "EventListener.h"
#include "Model.h"
#include "Audio.h"

class Game;

class Tank : public Object, public EventListener
{
	public:
		Tank(Game *gmae, float x, float y, float z, float direction);
		~Tank();
		void draw() const;
		void input(const SDL_Event *events);
		void update();

	private:
		float direction;
		bool front, back;
		bool left, right;
		Audio *soundShot;
		Game *game;
		Model *model;
		void shot();
};

#endif