#ifndef _GAME_
#define _GAME_

#include "SDL/SDL.h"
#include <list>
#include "Renderer.h"
#include "EventListener.h"

class Game
{
	public:
		Game();
		~Game();
		/**
		 * Adiciona um objeto o lista de objetos do jogo.
		 */
		void addObject(Object *d);
		/**
		 * Adiciona um ouvinte de eventos ao jogo,
		 * para ser notificado sobre os eventos.
		 */
		void addEventListener(EventListener *e);
		/**
		 * Remove um objeto da lista e o deleta.
		 * Obs.: o objeto nem sempre será removido
		 * imediatamente.
		 */
		void removeObject(Object *d);
		/**
		 * Remove o ouvinte de evento do jogo,
		 * para então para de ser notificado.
		 */
		void removeEventListener(EventListener *e);
		/**
		 * Chamado para atualizar o jogo.
		 */
		void update();
		/**
		 * Chamado quando ocorre eventos, e então
		 * os distribui para todo o jogo.
		 */
		void writeEvents(const SDL_Event *events);
		/**
		 * Desenha/Redesenha todos os objetos válidos do jogo.
		 */
		void draw() const;
		/**
		 * Obtém o lista que contém os objetos do
		 * jogo.
		 */
		std::list<Object*>* getObjects();
		/**
		 * Informa se o jogo acabou.
		 */
		bool isFinished();

	private:
		std::list<Object*> *objects;
		std::list<Object*> *trash;
		std::list<EventListener*> *listeners;
		bool finished;
		void initList();
		void trashDiscard();
};

#endif