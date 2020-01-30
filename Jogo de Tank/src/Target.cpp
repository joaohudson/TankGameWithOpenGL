#include "Target.h"
#include "Object.h"
#include "Game.h"
#include "Renderer.h"

static int count = 0;

Target::Target(Game *game, float x, float y, float z, float direction) : Object(game, x, y, z)
{
	this->direction = direction;
	this->width = 5.0f;
	this->height = 5.0f;
	this->depth = 5.0f;
	texture = renderer::loadTexture("res/images/target.png");
	count++;
}

Target::~Target()
{
	glDeleteTextures(1, &texture);
}

int Target::getCount()
{
	return count;
}

void Target::resetCount()
{
	count = 0;
}

void Target::destroy()
{
	game->removeObject(this);
	count--;
}

void Target::draw() const
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glPushMatrix();

		glTranslatef(x, y, z);
		glRotatef(direction, 0, 1, 0);

		glBegin(GL_QUADS);
		{
			glColor3f(1.0f, 1.0f, 1.0f);

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