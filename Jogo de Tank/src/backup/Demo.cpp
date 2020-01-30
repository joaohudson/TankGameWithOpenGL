#include "Demo.h"
#include "Game.h"

#define VELOCITY 10 
#define TETA_VELOCITY 2

Demo::Demo(int x, int y, int width, int height, const char *dirAudio, Game *game) : Object(x, y, width, height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->game = game;

	dleft = false;
	dright = false;
	dup = false;
	ddown = false;
	tetaLeft = false;
	tetaRight = false;
	dteta = 0;

	game->addEventListener(this);

	if(dirAudio != NULL)
		audio = new Audio(dirAudio);
	else
		audio = NULL;

	texture = renderer::loadTexture("res/images/nave.png");
}

Demo::~Demo()
{
	delete audio;
	glDeleteTextures(1, &texture);
}

void Demo::draw() const
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glLoadIdentity();

	glPushMatrix();

	glRotatef(dteta, 0, 1, 0);

	glBegin(GL_QUADS);
	{
		//Ao mudar a cor, essa cor será misturada a textura. Branco é o neutro:
		glColor4ub(255, 255, 255, 255);

		glTexCoord2f(0, 0);
		glVertex2f(x, y);

		glTexCoord2f(0, 1);
		glVertex2f(x, y + height);

		glTexCoord2f(1, 1);
		glVertex2f(x + width, y + height);

		glTexCoord2f(1, 0);
		glVertex2f(x + width, y);
	}
	glEnd();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void Demo::input(const SDL_Event *e)
{
	if(e->type == SDL_KEYDOWN)
		switch (e->key.keysym.sym)
		{
			case SDLK_UP:
				dup = true;
				break;

			case SDLK_DOWN:
				ddown = true;
				break;

			case SDLK_LEFT:
				dleft = true;
				break;

			case SDLK_RIGHT:
				dright = true;
				break;

			case SDLK_r:
				tetaLeft = true;
				break;

			case SDLK_e:
				tetaRight = true;
				break;

			case SDLK_0:
				dteta = 0;
				break;

			case SDLK_SPACE:
				if(audio != NULL)
					audio->play();
		}

	if(e->type == SDL_KEYUP)
		switch (e->key.keysym.sym)
		{
			case SDLK_UP:
				dup = false;
				break;

			case SDLK_DOWN:
				ddown = false;
				break;

			case SDLK_LEFT:
				dleft = false;
				break;

			case SDLK_RIGHT:
				dright = false;
				break;

			case SDLK_r:
				tetaLeft = false;
				break;

			case SDLK_e:
				tetaRight = false;
		}
}

void Demo::update()
{
	if(dleft)
		x -= VELOCITY;
	if(dright)
		x += VELOCITY;
	if(dup)
		y -= VELOCITY;
	if(ddown)
		y += VELOCITY;
	if(tetaLeft)
		dteta += TETA_VELOCITY;
	if(tetaRight)
		dteta -= TETA_VELOCITY;
}