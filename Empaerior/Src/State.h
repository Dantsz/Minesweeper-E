#pragma once
#include "Sprite.h"
/*
	A state of the game engine.
*/


class State
{
public:
	State();
	void Update(const unsigned int& dt);
	void Render();//renders the state
	void set_camera(const SDL_Rect& rect);//sets the camera to the specified sdl rect
	std::shared_ptr<Camera> get_camera() { return camera; } // return a shared pointer to the camera

	Text_Sprite* norge;
private:
	std::shared_ptr<Camera> camera;

	Sprite* morge;
};