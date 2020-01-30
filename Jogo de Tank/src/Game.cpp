#include "Game.h"
#include "Demo.h"
#include "Projectile.h"
#include "Tank.h"
#include "Target.h"
#include <iostream>
#include <string>

using std::list;
using std::cout;
using std::endl;
using std::string;

Game::Game()
{
	finished = false;
	map = new Model("res/models/map.obj", "res/images/map.png");
	time = new Time(30);
	time->start();
	
	//Inicializa os recuros:
	models[RES_TANK] = new Model("res/models/tank.obj", "res/images/tank.png");
	models[RES_PROJECTILE] = new Model("res/models/projectile.obj", "res/images/projectile.png");

	initList();
}

Game::~Game()
{
	for(Object *o : objects)
	{
		delete o;
	}

	for(int i = 0; i < MODELS_NUMBER; i++)
	{
		delete models[i];
	}

	delete time;
	delete map;

	Target::resetCount();

	objects.clear();
	trash.clear();
	listeners.clear();
}

void Game::addObject(Object *d)
{
	objects.push_back(d);
}

void Game::addEventListener(EventListener *e)
{
	listeners.push_back(e);
}

void Game::removeObject(Object *d)
{
	trash.push_back(d);
}

void Game::removeEventListener(EventListener *e)
{
	listeners.remove(e);
}

void Game::trashDiscard()
{
	list<Object*> newList;
	bool isTrash = false;

	for(Object *o : objects)
	{
		for(Object *t : trash)
		{
			if(o == t)
			{
				isTrash = true;
				delete o;
			}
		}

		if(!isTrash)
			newList.push_back(o);

		isTrash = false;
	}

	objects.clear();
	trash.clear();
	objects = newList;
}

void Game::update()
{
	for(Object *o : objects)
	{
		o->update();
	}

	time->update();

	string str = "Tank Battle: Survivor - Time: ";
	str = str + std::to_string(time->getCount());

	SDL_WM_SetCaption(str.c_str(), NULL);

	if(!Target::getCount())
	{	
		reset = true;
		victory = true;
	}
	else if(time->finished())
	{
		victory = false;
		reset = true;
	}

	//Descarta os objetos marcados para o descarte:
	trashDiscard();
}

void Game::writeEvents(const SDL_Event *events)
{
	for(EventListener *l : listeners)
	{
		l->input(events);
	}
}

void Game::draw() const
{
	for(Object *o : objects)
	{
		o->draw();	
	}

	//Desenha o mapa:
	glPushMatrix();
		glTranslatef(0, -5, 0);
		glScalef(20, 10, 20);
		glColor3f(1.0f, 1.0f, 1.0f);
		map->draw();
	glPopMatrix();
}

bool Game::isVictory()
{
	return victory;
}

const std::list<Object*>& Game::getObjects()
{
	return objects;
}

Model* Game::findModel(ResModel model)
{
	return models[model];
}

bool Game::resetGame()
{
	bool aux = reset;
	reset = false;

	return aux;
}

bool Game::isFinished()
{
	return finished;
}

void Game::initList()
{
	Target *target;

	for(int i = 0; i < 15; i++)
	{
		target = new Target(this, 150.0f - i * 20.0f, 0.0f, 150.0f, 0.0f);
		objects.push_back(target);	
	}

	for(int i = 0; i < 10; i++)
	{
		target = new Target(this, 150.0f, 0.0f, 130.0f - i * 20.0f, 90.0f);
		objects.push_back(target);	
	}

	Tank *tank = new Tank(this, 0, 0, -10, 0.0f);
	objects.push_back(tank);
	listeners.push_back(tank);
}
