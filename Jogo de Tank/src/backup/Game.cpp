#include "Game.h"
#include "Demo.h"

using std::list;

Game::Game()
{
	objects = new list<Object*>();
	trash = new list<Object*>();
	listeners = new list<EventListener*>();
	finished = false;
	initList();
}

Game::~Game()
{
	list<Object*>::iterator it;

	for(it = objects->begin(); it != objects->end(); it++)
	{
		delete *it;
	}

	objects->clear();
	trash->clear();
	listeners->clear();
 
	delete objects;
	delete trash;
	delete listeners;
}

void Game::addObject(Object *d)
{
	objects->push_back(d);
}

void Game::addEventListener(EventListener *e)
{
	listeners->push_back(e);
}

void Game::removeObject(Object *d)
{
	trash->push_back(d);
}

void Game::removeEventListener(EventListener *e)
{
	listeners->remove(e);
}

void Game::trashDiscard()
{
	Object *o, *o2;
	list<Object*>::iterator it, it2;

	for(it = objects->begin(); it != objects->end(); it++)
	{
		o = *it;

		for(it2 = trash->begin(); it2 != trash->end(); it2++)
		{
			o2 = *it2;

			//Deleta o objeto se ele estiver contido na lista de descarte:
			if(o == o2)
			{
				objects->erase(it);
				delete o;
			}
		}
	}
}

void Game::update()
{
	list<Object*>::iterator it;

	for(it = objects->begin(); it != objects->end(); it++)
	{
		(*it)->update();
	}

	//Descarta os objetos marcados para o descarte:
	trashDiscard();
}

void Game::writeEvents(const SDL_Event *events)
{
	list<EventListener*>::iterator it;

	for(it = listeners->begin(); it != listeners->end(); it++)
	{
		(*it)->input(events);
	}
}

void Game::draw() const
{
	list<Object*>::iterator it;

	for(it = objects->begin(); it != objects->end(); it++)
	{
		(*it)->draw();	
	}
}

std::list<Object*>* Game::getObjects()
{
	return objects;
}

bool Game::isFinished()
{
	return finished;
}

void Game::initList()
{
	Demo *demo;

	demo = new Demo(10, 10, 50, 50, "res/sounds/shot.wav", this);
	objects->push_back(demo);
	listeners->push_back(demo);

	demo = new Demo(110, 10, 50, 50, NULL, this);
	objects->push_back(demo);
	listeners->push_back(demo);

	demo = new Demo(10, 110, 50, 50, NULL, this);
	objects->push_back(demo);
	listeners->push_back(demo);

	demo = new Demo(60, 10, 50, 50, NULL, this);
	objects->push_back(demo);
	listeners->push_back(demo);

	demo = new Demo(10, 60, 50, 50, NULL, this);
	objects->push_back(demo);
	listeners->push_back(demo);

	demo = new Demo(60, 60, 50, 50, NULL, this);
	objects->push_back(demo);
	listeners->push_back(demo);

	demo = new Demo(110, 110, 50, 50, NULL, this);
	objects->push_back(demo);
	listeners->push_back(demo);

	demo = new Demo(160, 160, 50, 50, NULL, this);
	objects->push_back(demo);
	listeners->push_back(demo);
}
