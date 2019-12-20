#pragma once
#include <SDL.h>
bool rect_contains_point(const SDL_Rect& rect,int x, int y )
{


	if (y <= rect.y || y > rect.y + rect.h) return false;
	if (x <= rect.x || x > rect.x + rect.w) return false;
	
	return true;
}