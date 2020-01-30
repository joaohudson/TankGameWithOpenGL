#include "Renderer.h"
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "SDL/SDL_image.h"
#include "ScreenDimension.h"
#include "Game.h"
#include <math.h>

using namespace renderer;
using std::list;

//Dados da luz:
static const GLfloat ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f};
static const GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f};
static const GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
static const GLfloat position0[] = {1.0f, 0.0f, 0.0f, 1.0f};

static float teste = 0.0f;

//Posição da câmera:
static float camX = 0.0f, camY = 0.0f, camZ = 1.0f;
//Ponto para onde a câmera olha(define a direção da visão na horizontal):
static float camCenterX = 0.0f, camCenterZ = 0.0f, camCenterY = 0.0f;

static void updateLight()
{	
	GLfloat reflectance[] =  {1.0f, 1.0f, 1.0f, 1.0f};

	glMaterialfv(GL_FRONT, GL_SPECULAR, reflectance);
	glMateriali(GL_FRONT, GL_SHININESS, 20);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);
}

void renderer::fixeCam(float angle, float x, float y,  float z, float altura, float distanci)
{
	//Pega a versão em radianos do ângulo:
	float rad = angle / 57.29578f;

	camCenterX = x;
	camCenterZ = z;
	camCenterY = y;
	camX = x - distanci * sin(rad);
	camY = altura;
	camZ = z - distanci * cos(rad);
}

void renderer::init()
{
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_DEPTH_TEST);
	//Ativa a iluminação:
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	//Ativa a primeira luz:
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
}

void renderer::update(const Game *game)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	updateLight();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(54.0f, SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//gluPerspective(54.0f, SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 100.0f);
	gluLookAt(camX, camY, camZ,
			  camCenterX, 0.0f, camCenterZ,
			  0.0f, 1.0f, 0.0f);

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