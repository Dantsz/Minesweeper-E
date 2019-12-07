
#include <crtdbg.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "EventHandler.h"
//



#include "Game.h"



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
State* Empaerior::Game::cur_state;
const Uint32 Empaerior::Game::dt = 1000 / 60;
Uint32 Empaerior::Game::width  = 960;
Uint32 Empaerior::Game::height = 800;
bool Empaerior::Game::is_paused = 0;
bool Empaerior::Game::is_running = 1;
Empaerior::Window Empaerior::Game::window;
#pragma endregion

Empaerior::Game* game;


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
	
	Empaerior::Game* game = new Empaerior::Game();
	
	game->Init();


	Uint32 framestart = 0;
	Uint32 frametime = 0;
	Uint32 currentime = 0;
	Uint32 acumulator = 0;


	EventListener evy;
	evy.register_event(SDL_KEYUP, [](SDL_Event const& event) {
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			std::cout << "shoudl quit now" << '\n';
		}
		});




	try {
		while (Empaerior::Game::is_running)
		{




		
			//not a permanent solution to handle events
			while (SDL_PollEvent(&event)) {

				evy.handleEvents(event);
				switch (event.type)
				{
				case SDL_QUIT:
					Empaerior::Game::is_running = false;
					break;


				case SDL_WINDOWEVENT:
					switch (event.window.event) {
					case SDL_WINDOWEVENT_MINIMIZED:
						Empaerior::Game::is_paused = true;
						std::cout << "minimized";
						break;

					case SDL_WINDOWEVENT_RESTORED:
						Empaerior::Game::is_paused = false;
						std::cout << "maximized";
						break;
					}

					break;


				}
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

			
				

				//I use this to test for leaks//

				//Text_Sprite * norge = new Text_Sprite({ 0,0,200,200 }, "assets/font.ttf", 32 ,s, color);
				Empaerior::Sprite* norge = new Empaerior::Sprite({ 0,0,100,100 }, { 0,0100,100 }, "assets/img.png", 1);


				Empaerior::Game::window.clear();
				game->render();
				norge->draw(cam);
				Empaerior::Game::window.render();

				delete norge;
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
	
	return 0;
}