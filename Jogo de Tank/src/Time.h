#ifndef _TIME_
#define _TIME_

#include "SDL/SDL_timer.h"

class Time
{
	public:
	Time(int seconds);
	void start();
	void update();
	int getCount();
	bool finished();

	private:
	int maxSeconds;
	int seconds;
	Uint32 lastTime;
};

#endif