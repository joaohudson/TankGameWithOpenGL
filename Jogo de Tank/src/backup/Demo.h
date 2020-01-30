#ifndef _DEMO_
#define _DEMO_

#include "Renderer.h"
#include "Object.h"
#include "Audio.h"
#include "EventListener.h"

class Game;

class Demo : public Object, public EventListener
{
	public:
		Demo(int x, int y, int width, int height, const char *dirAudio, Game *game);
		~Demo();
		void draw() const;
		void input(const SDL_Event *e);
		void update();
	private:
		bool dleft, dright;
		bool dup, ddown;
		bool tetaLeft, tetaRight;
		float dteta;
		GLuint texture;
		Audio *audio;
		Game *game;

};

#endif