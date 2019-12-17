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
	Empaerior::Timer timy;
	ecs.Init();
	ecs.register_component<Empaerior::Print_Component>();
	ecs.register_component<Empaerior::Position_Component>();
	ecs.register_component<Empaerior::Camera_Component>();
	printy = ecs.register_system<Print_System>();
	ecs.add_component_to_system<Empaerior::Print_Component, Print_System>();


		morge.id = ecs.create_entity_ID();
	


	ecs.add_component<Empaerior::Print_Component>(morge.id, Empaerior::Print_Component{ "morgeee" });
	ecs.add_component<Empaerior::Position_Component>(morge.id, Empaerior::Position_Component{ 10,10 });
	ecs.add_component<Empaerior::Camera_Component>(morge.id, Empaerior::Camera_Component{ {0,0,960,800} });


		
	camera = ecs.get_component<Empaerior::Camera_Component>(morge.id).camera;

	



}

void State::Update(const unsigned int& dt)
{
	


	

	

}

void State::Render()
{

	

	if(norge != nullptr) norge->draw(Empaerior::Game::cur_state->camera);
}
	
void State::set_camera(const SDL_Rect& rect) 
{
	camera.set_dimensions(rect.w,rect.h);
	camera.set_position(rect.x, rect.y);
}
 