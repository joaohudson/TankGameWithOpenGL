#include "Renderer.h"
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "SDL/SDL_image.h"
#include "ScreenDimension.h"
#include "Game.h"

using namespace renderer;
using std::list;

void renderer::init()
{
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -100, 100);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void renderer::update(const Game *game)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	game->draw();
	
	SDL_GL_SwapBuffers();
}

GLuint renderer::loadTexture(const char *dir)
{
	GLuint id = 0, format;
	SDL_Surface *image = IMG_Load(dir);
	
	//Criamos um objeto de textura e obtemos seu id
    glGenTextures(1, &id); 
 
    //Dizemos a OpenGL que iremos trabalhar com o objeto.
    glBindTexture(GL_TEXTURE_2D, id);
 
    //Filtro:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
 
    //Descobrimos o formato a partir da imagem:
    format = (image->format->BytesPerPixel == 3) ? GL_RGB : GL_RGBA;
 
    //Carregamos a imagem do disco:
    glTexImage2D(GL_TEXTURE_2D, 0, format, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);
 
	//Apaga a imagem original(o opengl agora tem uma cópia dela):
    SDL_FreeSurface(image);
	
	return id;
}