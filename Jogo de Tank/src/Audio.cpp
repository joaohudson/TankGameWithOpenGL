#include "SDL/SDL.h"
#include "Audio.h"

#define AUDIO_RATE  22050
#define AUDIO_FORMAT  AUDIO_S16SYS
#define AUDIO_CHANELS  2
#define AUDIO_BUFFERS  4096

//Número de áudios carregados:
static int nAudios = 0;

Audio::Audio(const char *dir)
{
    //Se é a primeira instância, inicia o sistema:
    if(nAudios == 0)
        Mix_OpenAudio(AUDIO_RATE, AUDIO_FORMAT, AUDIO_CHANELS, AUDIO_BUFFERS);

    //Incrementa a conatagem de áudios, e carrega o áudio:
    nAudios++;
    audio = Mix_LoadWAV(dir);
    inLoop = false;
}

Audio::~Audio()
{
    //Libera o áudio e decrementa a contagem:
    Mix_FreeChunk(audio);
    nAudios--;

    //Se não tem mais áudios sendo reproduzidos, encerra os sistema:
    if(nAudios == 0)
        Mix_CloseAudio();
}

void Audio::play()
{
    chanel = Mix_PlayChannel(-1, audio, 0);
}

void Audio::loop(int rep)
{
    if(rep < 0)
        rep = 0;

    inLoop = true;
    chanel = Mix_PlayChannel(-1, audio, rep);
}

void Audio::loop()
{
    inLoop = true;
    chanel = Mix_PlayChannel(-1, audio, -1);
}

void Audio::pause()
{
    inLoop = false;
    Mix_Pause(chanel);
}

bool Audio::isPlaying()
{
    return Mix_Playing(chanel) && inLoop;
}