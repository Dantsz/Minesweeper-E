#include "pch.h"
#include "State.h"
#include "Game.h"
#include <SDL.h>
//for testing
#include<iostream>
#include <string>
#include "utilities/Timer.h"

struct sdl_deleter
{
	void operator()(SDL_Window* p) const { SDL_DestroyWindow(p); }
	void operator()(SDL_Renderer* p) const { SDL_DestroyRenderer(p); }
	void operator()(SDL_Texture* p) const { SDL_DestroyTexture(p); }
};


State::State()

{

	ecs.Init();

	ecs.register_component<Empaerior::Position_Component>();
	ecs.register_component<Empaerior::Camera_Component>();
	ecs.register_component<Empaerior::Sprite_Component>();
	ecs.register_component<Empaerior::Event_Listener_Component>();
	ecs.register_component<Mine_field>();


	spr_system = ecs.register_system <Sprite_System>();
	event_system = ecs.register_system<Event_System>();
	mine_system = ecs.register_system<Mine_sweep_system>();

	ecs.add_component_to_system<Empaerior::Sprite_Component, Sprite_System>();
	ecs.add_component_to_system<Empaerior::Event_Listener_Component, Event_System>();
	

	//add the components to the mine field system
	//
	ecs.add_component_to_system<Empaerior::Sprite_Component, Mine_sweep_system>();
	



	camera = Empaerior::Camera({ 0,0,96,80 });
	
	
	Empaerior::Entity background = { ecs.create_entity_ID() };



	//creates the whole backgorund from one single pixel (weird)
	Empaerior::Sprite sprt ({0,0,96,80}, {0,0,1,1}, "assets/background.png", 1);
	ecs.add_component<Empaerior::Sprite_Component>(background.id, { {sprt} });
	ecs.add_component<Mine_field>(background.id, { {0} });


	//initialize the field
	#define tile ecs.get_component<Mine_field>(background.id).field[i][j]
	for (int i = 0; i < 16; i++)
	{
		for(int j =  0 ; j < 16; j++)
		{
		
			tile = ecs.create_entity_ID();
			//add the random generation here

			Empaerior::Sprite spr_tile({6 *  j ,5 * i ,6,5 }, { 0,0,16,16 }, "assets/tex_cell.png", 1);
			spr_tile.set_position(6 * j, 5 * i);

			ecs.add_component<Empaerior::Sprite_Component>(tile, { {spr_tile} });


		}
	
	}
	

	#undef tile

	


}

void State::Update(const unsigned int& dt)
{
	


	

	

}

void State::Render()
{

	
	spr_system->render(ecs,camera);
	
}
	
void State::set_camera(const SDL_Rect& rect) 
{
	camera.set_dimensions(rect.w,rect.h);
	camera.set_position(rect.x, rect.y);
}

void State::handleevents(const SDL_Event& event)
{
	event_system->handle_events(ecs, event);

}
 