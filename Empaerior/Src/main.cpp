
#include <crtdbg.h>

#include "Game.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include "Exceptions.h"
#include "SDL_Wrappers.h"
#include "Utilities.h"
#include  "Timer.h"

typedef uint32_t Uint32;

//static objects variables
#pragma region static objects
std::map<std::string, std::shared_ptr<SDL_Texture>> assetManager::Textures;
std::map<std::string, std::map<int, std::unique_ptr<TTF_Font>>> assetManager::Fonts;

std::map<std::string, std::unique_ptr<Mix_Chunk>> assetManager::Sounds;

/*SDL_Renderer* Game::renderer;
SDL_Window* Game::s_window;*/
State* Game::cur_state;
const Uint32 Game::dt = 1000 / 60;
Uint32 Game::width  = 960;
Uint32 Game::height = 800;
bool Game::is_paused = 0;
bool Game::is_running = 1;
Window Game::window;
#pragma endregion



Game* game;


int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	#pragma region SDL_Inititalization
	try {
		if (SDL::Init())
		{
			throw E_runtime_exception("Failed to initialize SDL", __FILE__, __LINE__);
		}
	}
	catch (E_runtime_exception & e)
	{
		std::cout << e.what() << '\n';
	}
	
	
	#pragma endregion


	Camera cam = { 0,0,100,100 };
	
	SDL_Event event;
	
	Game* game = new Game();
	
	game->Init();


	Uint32 framestart = 0;
	Uint32 frametime = 0;
	Uint32 currentime = 0;
	Uint32 acumulator = 0;


	try {
		while (Game::is_running)
		{




		
			//not a permanent solution to handle events
			SDL_PollEvent(&event);
			switch (event.type)
			{
				case SDL_QUIT:
					Game::is_running = false;
					break;

				
				case SDL_WINDOWEVENT:
					switch (event.window.event) {
					 case SDL_WINDOWEVENT_MINIMIZED:
						 Game::is_paused = true;
						 std::cout << "minimized";
						break;
					
					case SDL_WINDOWEVENT_RESTORED:
						Game::is_paused = false;
						std::cout << "maximized";
						break;
					}

					break;
				

			}
			
			if (!Game::is_paused)
			{
				

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

			
				

				//I use this to test for leaks//

				//Text_Sprite * norge = new Text_Sprite({ 0,0,200,200 }, "assets/font.ttf", 32 ,s, color);
				Sprite* norge = new Sprite({ 0,0,100,100 }, { 0,0100,100 }, "assets/img.png", 1);


				Game::window.clear();
				game->render();
				norge->draw(cam);
				Game::window.render();

				delete norge;
			}
		
			assetManager::clean_textures();

		}


	}
	catch (std::runtime_error & e)
	{
		std::cout <<e.what() << '\n';
	}
	
	Game::window.reset();

	assetManager::reset_assets();

	_CrtDumpMemoryLeaks();

	SDL::Quit();
	
	return 0;
}