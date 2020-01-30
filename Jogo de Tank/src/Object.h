#ifndef _OBJECT_
#define _OBJECT_

#include "Renderer.h"
#include <vector>

#define DEFAULT_DIM 0.25f

class Game;

class Object
{
	public:

	/**
	 * Cria um objeto, deve se especificar a posião
	 * x e y, e as dimensões width e height.
	 * Obs.: Dimensões não devem ser negativas.
	 */
	Object(Game *game, float x, float y, float width, float height);

	/**
	 * Cria um objeto, deve se especificar a posião
	 * x e y. Dimensões width e height padrão.
	 */
	Object(Game *game, float x, float y);

	/**
	 * Cria um objeto, deve se especificar a posião
	 * x ,y e z, e as dimensões width, height e depth.
	 * Obs.: Dimensões não devem ser negativas.
	 */
	Object(Game *game, float x, float y, float z, float width, float height, float depth);

	/**
	 * Cria um objeto, deve se especificar a posião
	 * x ,y e z. Dimensões width, height e depth padrão.
	 */
	Object(Game *game, float x, float y, float z);

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
	 * Move o objeto no plano xz de acordo
	 * com a distância e o ângulo dado.
	 */
	void moveXZ(float d, float angle);

	/**
	 * Impede que este objeto atravesse o objeto
	 * especificado.
	 */
	void block(const Object *o);

	/**
	 * Impede que este objeto saia do mapa.
	 */
	bool blockMap(float mapWidth, float mapDepth);

	/**
	 * Informa se o objeto especificado está em
	 * colisão com este.
	 */
	bool colision(const Object *o);

	/**
	 * Informa se o ponto especificado está
	 * dentro deste objeto.
	 */
	bool contains(float x, float y);
	
	protected:

	float x, y, z;
	float width, height, depth;
	Game *game;
};

#endif