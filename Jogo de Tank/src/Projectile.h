#ifndef _PROJECTILE_
#define _PROJECTILE_

#include "Object.h"
#include "Model.h"

class Tank;

class Projectile : public Object
{
	public:
	Projectile(Game *game, float x, float y, float z, float teta);
	~Projectile();
	void draw() const;
	void update();

	private:
	float teta;
	Model *model;

};

#endif