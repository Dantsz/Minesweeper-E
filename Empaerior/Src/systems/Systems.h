#pragma once

#include "core/exceptions/Exceptions.h"


#include "core/ecs/ECS.h"

#include "Component.h"
#include "rendering/objects/Sprite.h"
#include "eventhandler/EventHandler.h"


namespace Empaerior
{
	class Event_System : public Empaerior::System
	{
	public:

		~Event_System()
		{

		}

		void add_event_to_entity(Empaerior::ECS& ecs, const Empaerior::u_inter& entity_id, const Empaerior::u_int& event_type, std::function<void(Empaerior::Event&)> function , Empaerior::s_int call_times = -1)
		{
#define EVENTLISTENER  ecs.get_component<Empaerior::Event_Listener_Component>(entity_id).event_listener
			EVENTLISTENER.register_event(event_type, function, call_times);
#undef EVENTLISTENER
		}


		void handle_events(Empaerior::ECS& ecs,Empaerior::Event& event)
		{
#define EVENTLISTENER  ecs.get_component<Empaerior::Event_Listener_Component>(*Iterator).event_listener
			//REVERSE ITERATOR
			std::set<Empaerior::u_inter>::reverse_iterator Iterator = entities_id.rbegin();
			//ITERATING THROUGH THE ENTITIES IN REVERSE
			while (Iterator != entities_id.rend() && !Empaerior::is_event_handled(event))
			{
				EVENTLISTENER.handleEvents(event);
				Iterator++;
			}
			
			
			
			
#undef EVENTLISTENER

		}



	};

	/*
	New sprite system
	This is not finshed yet
	*/
	class Spr_System : public Empaerior::System
	{
#define COMPONENT ecs.get_component<Empaerior::Spr_Component>(id)
	public:
		// Creates a new sprite for the entity
		//Returns the index
		size_t emplace_sprite(Empaerior::ECS& ecs, const Empaerior::u_inter& id,

			const Empaerior::Float_Rect& m_rect, const Empaerior::Int_Rect& m_tex_rect, const Empaerior::string& tex_path, const  Empaerior::byte& m_frames)
		{
			if (COMPONENT.freed_indexes.empty())
			{
				//push a sprite
				COMPONENT.sprites.push_back({});
				//Initialize the sprite
				Empaerior::SpriteFunctions::InitSprite(COMPONENT.sprites[COMPONENT.sprites.size() - 1], m_rect, m_tex_rect, tex_path, m_frames);
				COMPONENT.spr_index.push_back(COMPONENT.sprites.size() - 1);
				//return index
				return COMPONENT.sprites.size() - 1;
			}
			else
			{
				//take the sprite from the front of the queue
				//reset
				Empaerior::SpriteFunctions::resetSPR(COMPONENT.sprites[COMPONENT.freed_indexes.front()]);
				//Init with new values
				Empaerior::SpriteFunctions::InitSprite(COMPONENT.sprites[COMPONENT.freed_indexes.front()], m_rect, m_tex_rect, tex_path, m_frames);
				//add it to be rendered
				COMPONENT.spr_index.push_back(COMPONENT.freed_indexes.front());
				//save the index
				size_t n_index = COMPONENT.freed_indexes.front();
				//pop the element
				COMPONENT.freed_indexes.pop();
				//return index
				return n_index;
			}
		}
		//	
		//Creates a text sprite
		//Returns the index
		size_t emplace_textsprite(Empaerior::ECS& ecs, const Empaerior::u_inter& id,
			const Empaerior::Float_Rect& m_rect, const Empaerior::string& font_path, const  Empaerior::u_inter& m_size, const Empaerior::string& message, Empaerior::Color m_color)
		{
			//the implementation is the same as for the normal sprite
			if (COMPONENT.freed_indexes.empty())
			{
				//push a sprite
				COMPONENT.sprites.push_back({});
				//Initialize the sprite
				Empaerior::SpriteFunctions::InitTextSprite(COMPONENT.sprites[COMPONENT.sprites.size() - 1], m_rect, font_path, m_size, message, m_color);
				COMPONENT.spr_index.push_back(COMPONENT.sprites.size() - 1);
				//return index
				return COMPONENT.sprites.size() - 1;
			}
			else
			{
				//take the sprite from the front of the queue
				//reset
				Empaerior::SpriteFunctions::resetSPR(COMPONENT.sprites[COMPONENT.freed_indexes.front()]);
				//Init with new values
				Empaerior::SpriteFunctions::InitTextSprite(COMPONENT.sprites[COMPONENT.sprites.size() - 1], m_rect, font_path, m_size, message, m_color);
				//add it to be rendered
				COMPONENT.spr_index.push_back(COMPONENT.freed_indexes.front());
				//save the index
				size_t n_index = COMPONENT.freed_indexes.front();
				//pop the element
				COMPONENT.freed_indexes.pop();
				//return index
				return n_index;
			}
		}
		//Deletes the sprite at the specified index
		void delete_sprite(Empaerior::ECS& ecs, const Empaerior::u_inter& id , const size_t index)
		{
			//find the element in the index vector and delete it

			Empaerior::boole is_found = false;
			size_t index_in_spr_index = -1;
			for (size_t i = 0; i < COMPONENT.spr_index.size(); i++)
			{
				if (COMPONENT.spr_index[i] == index) { index_in_spr_index = i; is_found = true; }
			}
			//if(is_found) // throw exception
			COMPONENT.spr_index.erase(COMPONENT.spr_index.begin() + index_in_spr_index);

			//put the index in the queue
			COMPONENT.freed_indexes.push(index);

		}

	
		//Update sprites
		void update(Empaerior::ECS& ecs, const Empaerior::u_int& dt)
		{
			for (auto& id : entities_id)
			{		
				for (auto& spr : COMPONENT.spr_index) COMPONENT.sprites[spr].update(dt);
			}
		}

		void render(Empaerior::ECS& ecs, Empaerior::Camera& camera)
		{
			for (auto& id : entities_id)
			{			
				for (auto& spr : COMPONENT.spr_index) COMPONENT.sprites[spr].draw(camera);
			}
		}

#undef COMPONENT
	};

	class T_E_System : public Empaerior::System
	{
	public:

		~T_E_System()
		{

		}

		using Timed_Function = std::function<void()>;




		//Adds a function to the container
		//time = the time between this function and the time *function* is called
		//call_number the number of times the function is called
		//the time resets after each function call
		void add_function(Empaerior::ECS& ecs, const Empaerior::u_inter& id, const Empaerior::u_inter& time, Timed_Function function, const Empaerior::s_inter call_number = -1)
		{
			//adds the necessary data in the containers
			ecs.get_component<T_E_Component>(id).time.emplace_back(time);
			ecs.get_component<T_E_Component>(id).functions.emplace_back(function);
			ecs.get_component<T_E_Component>(id).elapsed_time.emplace_back(0);
			ecs.get_component<T_E_Component>(id).call_times.emplace_back(call_number);
		}

	//iterates throught the container and executes the functions for which enough time has passed
#define component ecs.get_component<T_E_Component>(id)
		void Update(Empaerior::ECS& ecs, const Empaerior::u_int& dt)
		{
			for (auto& id : entities_id)
			{
				for (Empaerior::u_inter i = 0; i < component.functions.size(); i++)
				{
					component.elapsed_time[i] += dt;
					//if enought time has passed,execute the function and delete it from the registry
					if (component.elapsed_time[i] >= component.time[i])
					{
							//call function
							component.functions[i]();

							//if the function has been called *call_time* times
							if (component.call_times[i]  == 1)
							{
								//erase all
								component.elapsed_time.erase(component.elapsed_time.begin() + i);
								component.time.erase(component.time.begin() + i);
								component.functions.erase(component.functions.begin() + i);
							}
							else if (component.call_times[i] > 1)
							{
								--component.call_times[i] ;
							}
						

					}

				}

			}

		}
#undef component


	};
}