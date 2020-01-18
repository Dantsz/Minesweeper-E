#include "pch.h"
#include "Utilities.h"
#include "Game.h"
std::pair<float, float> Empaerior::get_world_mouse_coords(const Empaerior::Camera& camera)
{
	//get the positions
	std::pair<int, int> pos;
	std::pair<float, float> f_pos;


	SDL_GetMouseState(&pos.first, &pos.second);



	f_pos.first = float(pos.first);
	f_pos.second = float(pos.second);



	//Scale down the positions to match the world
	float sx = 0;
	float sy = 0;
	SDL_RenderGetScale(Empaerior::Game::window.renderer, &sx, &sy);
	
	f_pos.first /= sx;
	f_pos.second /= sy;




	//Transform for the position of the renderer
	SDL_Rect renderer_viewport;

	SDL_RenderGetViewport(Empaerior::Game::window.renderer, &renderer_viewport);
	f_pos.first -= renderer_viewport.x;
	f_pos.second -= renderer_viewport.y;

	//Transform the position relative to the camera dimesnions
	f_pos.first *= camera.rect.w;
	f_pos.second *= camera.rect.h;



	f_pos.first /= renderer_viewport.w;
	f_pos.second /= renderer_viewport.h;



	//Tranform for position
	f_pos.first += camera.rect.x;
	f_pos.second += camera.rect.y;




	return f_pos;
}
