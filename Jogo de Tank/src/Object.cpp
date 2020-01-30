#include <math.h>
#include "Object.h"
#include <iostream>

#define MOD(a) ((a) < 0 ? -a : a)

using std::cout;
using std::endl;

Object::Object(Game *game, float x, float y, float width, float height)
{
	this->game = game;
	this->x = x;
	this->y = y;
	z = 0.0f;
	this->width = width;
	this->height = height;
	depth = DEFAULT_DIM;
}

Object::Object(Game *game, float x, float y)
{
	this->game = game;
	this->x = x;
	this->y = y;
	z = 0.0f;
	width = DEFAULT_DIM;
	height = DEFAULT_DIM;
	depth = DEFAULT_DIM;
}

Object::Object(Game *game, float x, float y, float z, float width, float height, float depth) : Object(game, x, y, width, height)
{
	this->z = z;
	this->depth = depth;
}

Object::Object(Game *game, float x, float y, float z) : Object(game, x, y)
{
	this->z = z;
}

void Object::moveXZ(float d, float angle)
{
	//Pega a versão em radianos do ângulo:
	float rad = angle / 57.29578f;

	z += d * cos(rad);
	x += d * sin(rad); 
}

void Object::block(const Object *o)
{
	if(colision(o))
	{
		//Largura e altura do retângulo de intersecção:
		float w, d;
		//Verifica quem é o objeto da direita e pega a largura:
		if(x > o->x)
			w = (o->x + o->width) - (x - width);
		else
			w = (x + width) - (o->x - o->width);
		//Verifica quem é o objeto de traz e pega a profundidade:
		if(z > o->z)
			d = (o->z + o->depth) - (z - depth);
		else
			d = (z + depth) - (o->z - o->depth);

		//Se a largura for menor que a profundidade, afasta no x:
		if(w < d)
		{
			if(x > o->x)
				x = o->x + o->width + width;
			else
				x = o->x - (o->width + width);
		}
		else
		{
			if(z > o->z)
				z = o->z + o->depth + depth;
			else
				z = o->z - (o->depth + depth);
		}
	}
}

bool Object::blockMap(float w, float d)
{
	bool blocked = false;

	if(x + width > w)
	{
		x = w - width;
		blocked = true;
	}
	else if(x - width < -w)
	{
		x = width - w;
		blocked = true;
	}

	if(z + depth > d)
	{
		z = d - depth;
		blocked = true;
	}
	else if(z - depth < -d)
	{
		z = depth - d;
		blocked = true;
	}

	return blocked;
}

bool Object::colision(const Object *o)
{
	if(this == o)
		return false;

	float dx = o->x - x;
	float dz = o->z - z;
	float spaceX = o->width + width;
	float spaceY = o->height + height;
	float spaceZ = o->depth + depth;

	bool intersectX =  (dx < spaceX) && (dx > -spaceX);
	bool intersectY =  (dz < spaceY) && (dz > -spaceY);
	bool intersectZ =  (dz < spaceZ) && (dz > -spaceZ);

	return intersectX && intersectY && intersectZ;

	//float mx = x + width;
	//float my = y + height;
	//float mz = z + depth;
	//float nx = o->x + o->width;
	//float ny = o->y + o->height;
	//float nz = o->z + o->depth;

	//return mx >= o->x && my >= o->y && mz >= o->z && nx >= x && ny >= y && nz >= o->depth;
}

bool Object::contains(float x, float y)
{
	return (this->x + this->width >= x && x >= this->x) && (this->y + this->height >= y && y >= this->y);
}