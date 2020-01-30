#ifndef _DEMO_
#define _DEMO_

#include "Object.h"
#include "Audio.h"
#include "EventListener.h"

class Game;

class Demo : public Object, public EventListener
{
	public:
		Demo(Game *game, float x, float y, float width, float height, const char *dirAudio);
		~Demo();
		void draw() const;
		void input(const SDL_Event *e);
		void update();
	private:
		bool dleft, dright;
		bool dfront, dback;
		bool dup, ddown;
		bool tetaXLeft, tetaXRight;
		bool tetaYLeft, tetaYRight;
		float dtetaY;
		float dtetaX;
		GLuint texture;
		Audio *audio;

};

#endif