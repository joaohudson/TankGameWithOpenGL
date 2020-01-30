#include "Projectile.h"
#include "Tank.h"
#include "Game.h"
#include "Target.h"
#include <list>

#define VELOCITY 5.0f

using std::list;

Projectile::Projectile(Game *game, float x, float y, float z, float teta) : Object(game, x, y, z)
{
	model = game->findModel(RES_PROJECTILE);
	this->teta = teta;
	this->width = 1.0f;
	this->height = 1.0f;
	this->depth = 2.0f;
}

Projectile::~Projectile()
{

}

void Projectile::update()
{
	const list<Object*> &objs = game->getObjects();

	moveXZ(VELOCITY, teta);

	for(Object *o : objs)
	{
		if(dynamic_cast<Tank*>(o))
			continue;

		//Se colidiu com algum objeto:
		if(colision(o))
		{
			Target *target;
			//Se for um alvo destrói:
			if(target = dynamic_cast<Target*>(o))
				target->destroy();
			//Se auto-destrói e para a análise:
			game->removeObject(this);
			break;
		}

		if(blockMap(MAP_WIDTH, MAP_DEPTH))
		{
			//Se auto-destrói e para a análise:
			game->removeObject(this);
			break;
		}
	}
}

void Projectile::draw() const
{
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(teta, 0, 1, 0);
		model->draw();
	glPopMatrix();
}