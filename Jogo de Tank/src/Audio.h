#ifndef _AUDIO_
#define _AUDIO_

#include "SDL/SDL_mixer.h"

class Audio
{
	public:

		/**
		 * Cria um reprodutor de áudio do formato
		 * WAV, carregado apartir do diretótio especificado.
		 */
		Audio(const char *dir);

		/**
		 * Destrói esse reprodutor de áudio, e libera os recursos
		 * usados.
		 */
		~Audio();

		/**
		 * Reproduz o áudio.
		 */
		void play();

		/**
		 * Reproduz o áudio rep vezes.
		 */
		void loop(int rep);

		/**
		 * Reproduz o áudio repetidamente.
		 */
		void loop();

		/**
		 * Pausa o áudio.
		 */
		void pause();
		
		/**
		 * Informa se o áudio está tocando.
		 */
		bool isPlaying();
	
	private:
		bool inLoop;
		int chanel;
		Mix_Chunk *audio;
};

#endif