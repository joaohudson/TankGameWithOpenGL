#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "ScreenDimension.h"
#include "Renderer.h"
#include "Game.h"

using std::list;

static bool running = true;
static SDL_Event events;
static Game *game = NULL;

//Inicializa tudo:
void setup()
{
	//Inicializa o sistema SDL:
	SDL_Init(SDL_INIT_EVERYTHING);

	//Cria a janela:
	SDL_WM_SetCaption("Battle Tank: Survivor", NULL);
	SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_OPENGL | SDL_DOUBLEBUF | SDL_HWSURFACE);

	//Inicializa o renderer:
	renderer::init();

	//Cria o jogo:
	game = new Game();
}

void updateEvents()
{
	//Captura os eventos:
	if(SDL_PollEvent(&events))
	{
		//Enecerra o jogo ao fechar a janela:
		if(events.key.keysym.sym == SDLK_ESCAPE || events.type == SDL_QUIT)
			running = false;

		game->writeEvents(&events);
	}
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
	//Inicializa tudo:
	setup();

	while(running)
	{
		//Atualiza o jogo:
		updateEvents();
		updateGame();
		updateRenderer();
	}

	//Encerra o jogo:
	quit();

	return 0;
}