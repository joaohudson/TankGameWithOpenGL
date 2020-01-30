#include "Demo.h"
#include "Game.h"
#include "Renderer.h"
#include <iostream>

#define VELOCITY 0.5
#define TETA_VELOCITY 2

Demo::Demo(Game *game, float x, float y, float width, float height, const char *dirAudio) : Object(game, x, y, width, height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->depth = width;
	this->game = game;

	dleft = false;
	dright = false;
	dfront = false;
	dback = false;
	dup = false;
	ddown = false;
	tetaXLeft = false;
	tetaXRight = false;
	tetaYLeft = false;
	tetaYRight = false;
	dtetaX = 0.0f;
	dtetaY = 0.0f;

	game->addEventListener(this);

	if(dirAudio != NULL)
		audio = new Audio(dirAudio);
	else
		audio = NULL;

	texture = renderer::loadTexture("res/images/target.png");
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

	glPushMatrix();

		glTranslatef(x, y, z);
		glRotatef(dtetaY, 0, 1, 0);
		glRotatef(dtetaX, 1, 0, 0);

		glBegin(GL_QUADS);
		{
			//Ao mudar a cor, essa cor será misturada a textura. Branco é o neutro:
			glColor3f(0.8f, 0.8f, 0.8f);

			//Frente:
			glNormal3f(0.0f, 0.0f, -1.0f);

			glTexCoord2f(0, 0);
			glVertex3f(-width, -height, -depth);

			glTexCoord2f(1, 0);
			glVertex3f(width, -height, -depth);

			glTexCoord2f(1, 1);
			glVertex3f(width, height, -depth);

			glTexCoord2f(0, 1);
			glVertex3f(-width, height, -depth);

			//Traz:
			glNormal3f(0.0f, 0.0f, 1.0f);

			glVertex3f(-width, -height, depth);

			glVertex3f(width, -height, depth);

			glVertex3f(width, height, depth);

			glVertex3f(-width, height, depth);

			//Esquerda:
			glNormal3f(-1.0f, 0.0f, 0.0f);

			glVertex3f(-width, -height, -depth);

			glVertex3f(-width, -height, depth);

			glVertex3f(-width, height, depth);

			glVertex3f(-width, height, -depth);

			//Direita:
			glNormal3f(1.0f, 0.0f, 0.0f);

			glVertex3f(width, -height, -depth);

			glVertex3f(width, -height, depth);

			glVertex3f(width, height, depth);

			glVertex3f(width, height, -depth);

			//Baixo:
			glNormal3f(0.0f, -1.0f, 0.0f);

			glVertex3f(-width, -height, depth);

			glVertex3f(width, -height, depth);

			glVertex3f(width, -height, -depth);

			glVertex3f(-width, -height, -depth);

			//Cima:
			glNormal3f(0.0f, 1.0f, 0.0f);

			glVertex3f(-width, height, depth);

			glVertex3f(width, height, depth);

			glVertex3f(width, height, -depth);

			glVertex3f(-width, height, -depth);
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

			case SDLK_KP_PLUS:
				dfront = true;
				break;

			case SDLK_KP_MINUS:
				dback = true;
				break;

			case SDLK_r:
				tetaXLeft = true;
				break;

			case SDLK_e:
				tetaXRight = true;
				break;

			case SDLK_d:
				tetaYLeft = true;
				break;

			case SDLK_f:
				tetaYRight = true;
				break;

			case SDLK_0:
				dtetaX = 0;
				dtetaY = 0;
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

			case SDLK_KP_PLUS:
				dfront = false;
				break;

			case SDLK_KP_MINUS:
				dback = false;
				break;

			case SDLK_r:
				tetaXLeft = false;
				break;

			case SDLK_e:
				tetaXRight = false;
				break;

			case SDLK_d:
				tetaYLeft = false;
				break;

			case SDLK_f:
				tetaYRight = false;
		}
}

void Demo::update()
{
	/*
	if(dleft);
		x -= VELOCITY;
	if(dright);
		x += VELOCITY;
	if(dfront);
		z -= VELOCITY;
	if(dback);
		z += VELOCITY;
	if(dup) moveXZ(VELOCITY, dtetaY);
		//y += VELOCITY;
	if(ddown) moveXZ(-VELOCITY, dtetaY);
		//y -= VELOCITY;
	if(tetaXLeft)
		dtetaX += TETA_VELOCITY;
	if(tetaXRight)
		dtetaX -= TETA_VELOCITY;
	if(tetaYLeft)
		dtetaY += TETA_VELOCITY;
	if(tetaYRight)
		dtetaY -= TETA_VELOCITY;

	//renderer::fixeCam(dtetaY, x, z, 20);
	*/
}