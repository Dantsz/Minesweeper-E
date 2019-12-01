#include "Camera.h"
#include "Game.h"

void Camera::set_dimensions(const int& w, const int& h)
{
	
	rect.w = w;
	rect.h = h;
	if (this == Game::cur_state->get_camera().get())// if the camera is the one used to render
	{
		SDL_RenderSetLogicalSize(Game::renderer, rect.w, rect.h); // using letterboxing, not a huge deal
	}
	
}
