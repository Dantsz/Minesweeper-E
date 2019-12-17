#include "Game.h"


#define fullscreen 0





Empaerior::Game::Game()
{
	window.Init("test", 960, 800);
	
	first_state = new State();//add a new state
	//second_state = new State();

	set_state(first_state);
	first_state->get_camera().set_dimensions(960, 800);
	set_state(first_state);
	SDL_RenderSetLogicalSize(Game::window.renderer, Game::cur_state->get_camera().rect.w, Game::cur_state->get_camera().rect.h);



}

void Empaerior::Game::Init()
{
	SDL_Color color = { 255,0 ,255 ,255 };
	//second_state->norge = new Empaerior::Text_Sprite({0,0,200,200}, "assets/font.ttf", 32, "Aldo adsadshbadsh gbaytu gvasty dvastyadsvtyvdasty ilea   ",color );
	
	


}



void Empaerior::Game::set_state(State* new_state)
{
	cur_state = new_state;
	SDL_RenderSetLogicalSize(Game::window.renderer, new_state->get_camera().rect.w, new_state->get_camera().rect.h); // set the render size to the new state's camera

}

void Empaerior::Game::Update(const unsigned int& dt )
{
	//move camera

	unsigned char const* keys = SDL_GetKeyboardState(nullptr);
	if (keys[SDL_SCANCODE_UP])
	{
		Game::cur_state->get_camera().set_dimensions(Game::cur_state->get_camera().rect.w + 12, Game::cur_state->get_camera().rect.h + 10);
	}
	else if (keys[SDL_SCANCODE_DOWN])
	{
		Game::cur_state->get_camera().set_dimensions(Game::cur_state->get_camera().rect.w - 12, Game::cur_state->get_camera().rect.h - 10);
	}
	else if (keys[SDL_SCANCODE_W])
	{
		Game::cur_state->get_camera().set_position(Game::cur_state->get_camera().rect.x, Game::cur_state->get_camera().rect.y - 10);
	}
	else if (keys[SDL_SCANCODE_S])
	{
		Game::cur_state->get_camera().set_position(Game::cur_state->get_camera().rect.x , Game::cur_state->get_camera().rect.y + 10);
	}
	else if (keys[SDL_SCANCODE_A])
	{
		Game::cur_state->get_camera().set_position(Game::cur_state->get_camera().rect.x - 10, Game::cur_state->get_camera().rect.y);
	}
	else if (keys[SDL_SCANCODE_D])
	{
		Game::cur_state->get_camera().set_position(Game::cur_state->get_camera().rect.x + 10, Game::cur_state->get_camera().rect.y);
	}
	else if (keys[SDL_SCANCODE_RIGHT])
	{
		set_state(second_state);
	}
	else if (keys[SDL_SCANCODE_LEFT])
	{
		set_state(first_state);
	}




	cur_state->Update(Game::dt);


}

void Empaerior::Game::handlevents(const SDL_Event & event)
{
	Empaerior::Game::window.window_listener.handleEvents(event);

}

void Empaerior::Game::render()
{
	
	//SDL_RenderClear(Game::renderer);

	cur_state->Render();

	//SDL_RenderPresent(Game::renderer);

}

