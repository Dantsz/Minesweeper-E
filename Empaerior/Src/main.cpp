
#ifdef _DEBUG   
#ifndef DBG_NEW      
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )     
#define new DBG_NEW   
#endif
#endif

#include <crtdbg.h>


#include <fstream>
#include <sstream>

//



#include "Game.h"



#include "exceptions/Exceptions.h"
#include "SDLwrappers/SDL_Wrappers.h"
#include "utilities/Utilities.h"
#include  "utilities/Timer.h"

typedef uint32_t Uint32;

//static objects variables
#pragma region static objects
std::map<std::string, std::shared_ptr<SDL_Texture>> assetManager::Textures;
std::map<std::string, std::map<int, std::unique_ptr<TTF_Font>>> assetManager::Fonts;

std::map<std::string, std::unique_ptr<Mix_Chunk>> assetManager::Sounds;

/*SDL_Renderer* Game::renderer;
SDL_Window* Game::s_window;*/
State* Empaerior::Game::cur_state;
const Uint32 Empaerior::Game::dt = 1000 / 60;
bool Empaerior::Game::is_paused = 0;
bool Empaerior::Game::is_running = 1;
Empaerior::Window Empaerior::Game::window;

#pragma endregion

Empaerior::Game* game;


int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	#pragma region SDL_Inititalization
	try {
		uint16_t error_flags = SDL::Init();
		//check for errors
		if(error_flags & sdl)
		{
			throw E_runtime_exception("Failed to initialize SDL", __FILE__, __LINE__);
		}
		if (error_flags & sdl_image)
		{
			throw E_runtime_exception("Failed to initialize SDL Graphics", __FILE__, __LINE__);
		}
		if (error_flags & sdl_ttf)
		{
			throw E_runtime_exception("Failed to initialize SDL Font", __FILE__, __LINE__);
		}
		if (error_flags & sdl_mix)
		{
			throw E_runtime_exception("Failed to initialize SDL Audio", __FILE__, __LINE__);
		}

	}
	catch (E_runtime_exception & e)
	{
		std::cout << e.what() << '\n';
	}
	
	
	#pragma endregion


	Camera cam = { 0,0,100,100 };
	
	SDL_Event event;
	
	Empaerior::Game* game = new Empaerior::Game();
	
	game->Init();


	Uint32 framestart = 0;
	Uint32 frametime = 0;
	Uint32 currentime = 0;
	Uint32 acumulator = 0;

	
	



	try {
		while (Empaerior::Game::is_running)
		{




		
		
			//not a permanent solution to handle events
			while (SDL_PollEvent(&event)) {

				game->handlevents(event);
				
			}
			if (!Empaerior::Game::is_paused)
			{
				

				framestart = SDL_GetTicks();
				frametime = framestart - currentime;

				if (frametime > 25) frametime = 25; //if too many frames are skipped

				currentime = framestart;
				acumulator += frametime;


				
				while (acumulator >= Empaerior::Game::dt)
				{
					//update 

					game->Update(Empaerior::Game::dt);
					
					acumulator -= Empaerior::Game::dt;



				}
				

				//Text_Sprite * norge = new Text_Sprite({ 0,0,200,200 }, "assets/font.ttf", 32 ,s, color);
			


				Empaerior::Game::window.clear();
				game->render();
				
				Empaerior::Game::window.render();

				
			}
		
			assetManager::clean_textures();

		}


	}
	catch (std::runtime_error & e)
	{
		std::cout <<e.what() << '\n';
	}
	
	Empaerior::Game::window.reset();

	assetManager::reset_assets();

	
	
	_CrtDumpMemoryLeaks();

	SDL::Quit();
	delete game;
	return 0;
}