#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "ScreenDimension.h"
#include "Renderer.h"
#include "Game.h"
#include "Model.h"
#include "SDL/SDL_ttf.h"
#include <iostream>

using namespace std;

static bool running = true;
static SDL_Event events;
static Game *game = NULL;
static unsigned int textVictory;

//Inicializa tudo:
void setup()
{
	//Inicializa o sistema SDL:
	SDL_Init(SDL_INIT_EVERYTHING);

	//Cria a janela:
	SDL_WM_SetCaption("Tank Battle: Survivor", NULL);
	SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_OPENGL | SDL_DOUBLEBUF);

	//Inicializa o renderer:
	renderer::init();

	textVictory = renderer::loadTexture("res/images/target.png");

	//Cria o jogo:
	game = new Game();
}

void updateEvents()
{
	//Captura os eventos:
	while(SDL_PollEvent(&events))
	{
		//Enecerra o jogo ao fechar a janela:
		if(events.key.keysym.sym == SDLK_ESCAPE || events.type == SDL_QUIT)
			running = false;

		game->writeEvents(&events);
	}
}

void waitComand(bool victory)
{
	bool wait = true;

	SDL_WM_SetCaption( victory ? "WIN (PRESS ENTER TO CONTINUE)" : "LOSE (PRESS ENTER TO CONTINUE)", NULL);

	while(wait)
	{
		SDL_PollEvent(&events);
		if(events.type == SDL_KEYDOWN && events.key.keysym.sym == SDLK_RETURN)
			wait = false;
	}

	SDL_WM_SetCaption("Tank Battle: Survivor", NULL);
}

void updateGame()
{
	//Atualiza o jogo:
	game->update();
}

void updateRenderer()
{
	//Desenha a tela:
	renderer::update(game);
}

void quit()
{
	delete game;
	SDL_Quit();
}

int main()
{
	setup();

	while(running)
	{
		//Atualiza o jogo:
		updateEvents();
		updateGame();
		updateRenderer();

		//Se o jogo desejar, reseta-o:
		if(game->resetGame())
		{
			waitComand(game->isVictory());
			delete game;
			game = new Game();
		}
	}

	//Encerra o jogo:
	quit();

	return 0;
}