#ifndef _GAME_
#define _GAME_

#include "SDL/SDL.h"
#include <list>
#include "Renderer.h"
#include "EventListener.h"
#include "Model.h"
#include "Time.h"

#define MAP_WIDTH 155.0f
#define MAP_DEPTH 155.0f
#define MODELS_NUMBER 2

enum ResModel{
	RES_TANK = 0, RES_PROJECTILE
};

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
		const std::list<Object*>& getObjects();
		/**
		 * Obtém um recurso do jogo.
		 */
		Model* findModel(ResModel model);
		/**
		 * Informa se o jogo acabou.
		 */
		bool isFinished();
		/**
		 * Informa se o jogador venceu ou não.
		 */
		bool isVictory();
		/**
		 * Informa se o jogo deve ser resetado.
		 */
		bool resetGame();

	private:
		std::list<Object*> objects;
		std::list<Object*> trash;
		std::list<EventListener*> listeners;
		Model *map;
		Model *models[MODELS_NUMBER];
		Time *time;
		bool finished;
		bool reset;
		bool victory;
		void initList();
		void trashDiscard();
};

#endif