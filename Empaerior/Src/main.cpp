

#include "Game.h"

#include <fstream>
#include <sstream>
#include <iostream>

typedef uint32_t Uint32;

//static objects variables
#pragma region static objects
std::map<std::string, std::shared_ptr<SDL_Texture>> assetManager::Textures;
std::map<std::string, std::map<int, std::unique_ptr<TTF_Font>>> assetManager::Fonts;

std::map<std::string, std::unique_ptr<Mix_Chunk>> assetManager::Sounds;

SDL_Renderer* Game::renderer;
SDL_Window* Game::window;
State* Game::cur_state;
const Uint32 Game::dt = 1000 / 60;
Uint32 Game::width  = 960;
Uint32 Game::height = 800;
#pragma endregion



Game* game;


int main(int argc, char** argv)
{
	#pragma region SDL_Inititalization
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{

	}


	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	TTF_Init();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		
	}
	
	#pragma endregion




	bool quit = false;
	SDL_Event event;
	
	Game* game = new Game();
	
	game->Init();
	
	Uint32 framestart = 0;
	Uint32 frametime = 0;
	Uint32 currentime = 0;
	Uint32 acumulator = 0;
	
	while (!quit)
	{

		
		
	
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		
		framestart = SDL_GetTicks();
		frametime = framestart - currentime;
		
		if (frametime > 25) frametime = 25; //if too many frames are skipped

		currentime = framestart;
	    acumulator += frametime;

		
		while (acumulator >= Game::dt)
		{
			//update 
		
			game->Update(Game::dt);
		
			acumulator -= Game::dt;
			


		}

		
		
	
		//Text_Sprite * norge = new Text_Sprite({ 0,0,200,200 }, "assets/font.ttf", 32 ,s, color);
		
		game->render();

		
		
		assetManager::clean_textures();
	}

	assetManager::clear_fonts();//clear all fonts so TTF_Quit doesn't throw an exceptions


	SDL_DestroyRenderer(Game::renderer);
	SDL_DestroyWindow(Game::window);
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	
	return 0;
}