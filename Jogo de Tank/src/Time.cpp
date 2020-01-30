#include "Time.h"

Time::Time(int maxSeconds)
{
	this->maxSeconds = maxSeconds;
	this->seconds = 0;	
}

void Time::start()
{
	lastTime = SDL_GetTicks();
}

int Time::getCount()
{
	return seconds;
}

bool Time::finished()
{
	return seconds >= maxSeconds;
}

void Time::update()
{
	seconds = (SDL_GetTicks() - lastTime) / 1000;

	if(seconds > maxSeconds) seconds = maxSeconds;
}