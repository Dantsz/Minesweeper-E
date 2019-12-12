#include "State.h"
#include "Game.h"
#include <SDL.h>
//for testing
#include<iostream>

struct sdl_deleter
{
	void operator()(SDL_Window* p) const { SDL_DestroyWindow(p); }
	void operator()(SDL_Renderer* p) const { SDL_DestroyRenderer(p); }
	void operator()(SDL_Texture* p) const { SDL_DestroyTexture(p); }
};


State::State()

{

	//test
	


	auto q = assetManager::load_font("assets/font.ttf", 36);
	camera = std::make_shared<Camera>(0,0, Empaerior::Game::window.get_width(), Empaerior::Game::window.get_heigth());


}

void State::Update(const unsigned int& dt)
{
	


}

void State::Render()
{

	

	if(norge != nullptr) norge->draw(*Empaerior::Game::cur_state->camera);
}

void State::set_camera(const SDL_Rect& rect) 
{
	camera->set_dimensions(rect.w,rect.h);
	camera->set_position(rect.x, rect.y);
}
