#ifndef _OBJECT_
#define _OBJECT_

#include "SDL/SDL.h"
#include <vector>

#define DEFAULT_DIM 50

class Object
{
	public:

	/**
	 * Cria um objeto, deve se especificar a posião
	 * x e y, e as dimensões width e height.
	 * Obs.: Dimensões não devem ser negativas.
	 */
	Object(int x, int y, int width, int height);

	/**
	 * Cria um objeto, deve se especificar a posião
	 * x e y. Dimensões width e height padrão.
	 */
	Object(int x, int y);

	/**
	 * Cria um objeto, deve se especificar a posião
	 * x ,y e z, e as dimensões width, height e depth.
	 * Obs.: Dimensões não devem ser negativas.
	 */
	Object(int x, int y, int z, int width, int height, int depth);

	/**
	 * Cria um objeto, deve se especificar a posião
	 * x ,y e z. Dimensões width, height e depth padrão.
	 */
	Object(int x, int y, int z);

	/**
	 * Destrói este objeto.
	 */
	virtual ~Object(){}
	
	/**
	 * Desenha este objeto, deve chamar funções do
	 * OpenGL para isto.
	 */
	virtual void draw() const = 0;
	
	/**
	 * Chamado repetidamente para atualizar o estado deste
	 * objeto.
	 */
	virtual void update() = 0;

	/**
	 * Informa se o objeto especificado está em
	 * colisão com este.
	 */
	bool colision(Object *o);

	/**
	 * Informa se o ponto especificado está
	 * dentro deste objeto.
	 */
	bool contains(int x, int y);
	
	protected:

	int x, y, z;
	int width, height, depth;
};

#endif