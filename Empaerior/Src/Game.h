#pragma once
#include "AssetManager.h"
#include "Sprite.h"
#include "Glyphs.h"
#include "State.h"
#include "Window.h"
namespace  Empaerior{
class Game
{
public:
	Game();

	void Init();


	 void create_window(const std::string& name, const int & width , const int&  height);
	 
	 void set_state(State* new_state); // sets a new state to be updated  & rendered 


	 void Update(const unsigned int& dt);
	 void handlevents();

	 void render();


private:



public:
	static State* cur_state;//current state

	State* first_state;
	State* second_state;


	/*static SDL_Renderer* renderer;
	static SDL_Window* s_window;*/
	
	static Empaerior::Window window;

	static const Uint32 dt;
	
	static Uint32 width;
	static Uint32 height;

	static bool is_paused;
	static bool is_running;
private:


	Empaerior::Text_Sprite* texy;



};
}