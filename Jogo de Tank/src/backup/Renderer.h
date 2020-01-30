#ifndef _RENDERER_
#define _RENDERER_

#include <list>
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "Object.h"

class Game;

namespace renderer
{
	/**
	 * Inicia o renderer.
	 */
	void init();

	/**
	 * Atualiza a tela renderizando a lista
	 * de objetos especificada.
	 */
	void update(const Game *game);

	/**
	 * Carrega uma textura, e retorna seu ID.
	 */
	GLuint loadTexture(const char *dir);
}

#endif