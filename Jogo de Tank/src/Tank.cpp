#include "Tank.h"
#include "Game.h"
#include "Renderer.h"
#include "Projectile.h"
#include <list>

#define VELOCITY 0.5f
#define DIRECTION_VELOCITY 0.8f

using std::list;

Tank::Tank(Game *game, float x, float y, float z, float direction) : Object(game, x, y, z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->game = game;
	this->direction = direction;

	this->width = 6.0f;
	this->height = 7.0f;
	this->depth = 7.0f;
	
	soundShot = new Audio("res/sounds/shot.wav");

	front = false;
	back = false;
	left = false;
	right = false;
	model = game->findModel(RES_TANK);
}

Tank::~Tank()
{
	delete soundShot;
}

void Tank::update()
{
	if(left)
		direction += DIRECTION_VELOCITY;
	if(right)
		direction -= DIRECTION_VELOCITY;
	if(front)
		moveXZ(VELOCITY, direction);
	if(back)
		moveXZ(-VELOCITY, direction);

	//Checa a colisão:
	list<Object*> objs = game->getObjects();
	
	for(Object *o : objs)
	{
		if(dynamic_cast<Projectile*>(o))
			continue;

		block(o);
	}
	//Impede que saia do mapa:
	blockMap(MAP_WIDTH, MAP_DEPTH);

	renderer::fixeCam(direction, x, y + 3.0f, z, y + 7.0f, 20.0f);
}

void Tank::draw() const
{
	glPushMatrix();
		glTranslatef(x, y - 3, z);
		glRotatef(direction, 0, 1, 0);
		glColor3f(0.4f, 0.4f, 0.4f);
		model->draw();
	glPopMatrix();
}

void Tank::input(const SDL_Event *events)
{
	if(events->type == SDL_KEYDOWN)
	{
		switch(events->key.keysym.sym)
		{
			case SDLK_UP:
				front = true;
				break;

			case SDLK_DOWN:
				back = true;
				break;

			case SDLK_LEFT:
				left = true;
				break;

			case SDLK_RIGHT:
				right = true;
				break;

			case SDLK_SPACE:
				shot();
		}
	}

	if(events->type == SDL_KEYUP)
	{
		switch(events->key.keysym.sym)
		{
			case SDLK_UP:
				front = false;
				break;

			case SDLK_DOWN:
				back = false;
				break;

			case SDLK_LEFT:
				left = false;
				break;

			case SDLK_RIGHT:
				right = false;
		}
	}
}

void Tank::shot()
{
	Projectile *p = new Projectile(game, x, y, z, direction);
	game->addObject(p);
	soundShot->play();
}