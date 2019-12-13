#pragma once

#include "graphics/rendering/objects/Sprite.h"
#include "graphics/rendering/Camera.h"

//entity tests
#include "entitysystem/Entity.h"

#include "entitysystem/components/ComponentManager.h"
#include "entitysystem/components/Component.h"

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
	Camera& get_camera() { return camera; } // return a shared pointer to the camera

	Empaerior::Text_Sprite* norge;
private:
	Camera camera;

	

	Empaerior::Entity morge;
	Empaerior::ComponentManager mangy;
};