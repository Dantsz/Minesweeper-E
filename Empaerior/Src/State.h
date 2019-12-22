#pragma once

#include "graphics/rendering/objects/Sprite.h"
#include "graphics/rendering/Camera.h"

//entity tests

#include "entitysystem/ECS.h"
#include "entitysystem/system/systems/print_system.h"
#include "entitysystem/system/systems/sprite_system.h"
#include "entitysystem/system/systems/event_system.h"
#include "entitysystem/system/systems/mine_sweeper_system.h"
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
	void handleevents(const SDL_Event& event);
	Empaerior::Camera& get_camera() { return camera; } // return a shared pointer to the camera

	std::shared_ptr<Mine_sweep_system> mine_system;
private:
	Empaerior::Camera camera;
	Empaerior::ECS ecs;

	
	
	std::shared_ptr<Sprite_System> spr_system;
	std::shared_ptr<Event_System> event_system;
	
	
	Empaerior::ComponentManager mangy;

	//id -> path to the png of the field (mine,1,2,3,0)
	std::unordered_map<int, std::string> id_to_field_type;
	//id -> path to the png of the cell type (flag,normal,?)
	std::unordered_map<int, std::string> id_to_cell_type;
};