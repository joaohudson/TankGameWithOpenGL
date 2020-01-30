#include "Object.h"

Object::Object(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	z = 0;
	this->width = width;
	this->height = height;
	depth = DEFAULT_DIM;
}

Object::Object(int x, int y)
{
	this->x = x;
	this->y = y;
	z = 0;
	width = DEFAULT_DIM;
	height = DEFAULT_DIM;
	depth = DEFAULT_DIM;
}

Object::Object(int x, int y, int z, int width, int height, int depth) : Object(x, y, width, height)
{
	this->z = z;
	this->depth = depth;
}

Object::Object(int x, int y, int z) : Object(x, y)
{
	this->z = z;
}

bool Object::colision(Object *o)
{
	if(this == o)
		return false;
		
	int mx = x + width;
	int my = y + height;
	int mz = z + depth;
	int nx = o->x + o->width;
	int ny = o->y + o->height;
	int nz = o->z + o->depth;

	return mx >= o->x && my >= o->y && mz >= o->z && nx >= x && ny >= y && nz >= o->depth;
}

bool Object::contains(int x, int y)
{
	return (this->x + this->width >= x && x >= this->x) && (this->y + this->height >= y && y >= this->y);
}