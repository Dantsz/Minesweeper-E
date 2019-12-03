#include<SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

namespace SDL {

	int Init()
	{
		return SDL_Init(SDL_INIT_EVERYTHING) < 0 || Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0 || TTF_Init() < 0 || IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0;
	}
	void Quit()
	{

		Mix_Quit();
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();

	}

}