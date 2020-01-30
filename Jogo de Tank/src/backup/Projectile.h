#ifndef _PROJECTILE_
#define _PROJECTILE_

#include "Object.h"

class Tank;

class Projectile : public Object
{
	public:
	Projectile(int x, int y, int z, float teta);
	~Projectile();
	void draw() const;
	void update();

	private:
	float teta;

};

#endif