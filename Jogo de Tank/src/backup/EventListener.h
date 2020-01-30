#ifndef _EVENT_LISTENER_
#define _EVENT_LISTENER_

#include "SDL/SDL.h"

class EventListener
{
	public:
	/**
	 * Recebe os eventos do SDL, quando eles
	 * ocorrem.
	 */
	virtual void input(const SDL_Event *events) = 0;

	/**
	 * Destrutor virtual, permite polimorfismo.
	 */
	virtual ~EventListener(){}
};

#endif