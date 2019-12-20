#include "pch.h"
#include "State.h"
#include "Game.h"
#include <SDL.h>
#include "utilities/collisions.h"
#include <SDL_mouse.h>
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



	//insert the path
	 int id = 0;
	 id_to_cell_type.insert({ id,"assets/tex_cell.png" });
	 ++id;
	 id_to_cell_type.insert({ id,"assets/tex_flag.png" });
	 ++id;
	 id_to_cell_type.insert({ id,"assets/tex_q.png" });










	//creates the whole backgorund from one single pixel (weird)
	Empaerior::Sprite sprt ({0,0,96,80}, {0,0,1,1}, "assets/background.png", 1);
	ecs.add_component<Empaerior::Sprite_Component>(background.id, { {sprt} });
	ecs.add_component<Mine_field>(background.id, { {0} });


	//initialize the field
	#define tile ecs.get_component<Mine_field>(background.id).field[i][j]
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{

			tile = ecs.create_entity_ID();
			//add the random generation here

			ecs.add_component<field_component>(tile, { 0 });
			ecs.add_component<cell_component>(tile, { 0 });
			ecs.add_component<Empaerior::Event_Listener_Component>(tile, { {} });

			//adds what at the bottom
			Empaerior::Sprite spr_tile({ 6 * j ,5 * i ,6,5 }, { 0,0,16,16 }, "assets/tex_empty.png", 1);



			//

			//adds what's in the front
			Empaerior::Sprite spr_cell({ 6 * j ,5 * i ,6,5 }, { 0,0,16,16 }, id_to_cell_type[0], 1);
		
			ecs.add_component<Empaerior::Sprite_Component>(tile, { {spr_tile,spr_cell} });
			
			//notice I didn't register this component as it is not necessary
			

			//event handling
			event_system->add_event_to_entity(ecs, tile, SDL_MOUSEBUTTONDOWN, [&Ecs = ecs,&mine = mine_system,map = background.id,i,j,kamera = camera ](SDL_Event const& event) {
			
			#define l_tile Ecs.get_component<Mine_field>(map).field[i][j]
				//mosue coordinates 
				int m_x = 0;
				int m_y = 0;
				SDL_GetMouseState(&m_x, &m_y);
				
				

				m_x *= kamera.rect.w;
				m_y *= kamera.rect.h;

				m_x /= 960;
				m_y /= 800;

				if (!Ecs.get_component<cell_component>(l_tile).is_revealed) 
				{ 
					if (rect_contains_point(Ecs.get_component<Empaerior::Sprite_Component>(l_tile).sprites[1].get_dimensions(),m_x,m_y))
					{
						mine->Reveal(Ecs, map, i, j);
					}
				}

			#undef l_tile
			});

			

		}
	
	}
	

	#undef tile

	//test
	


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
 