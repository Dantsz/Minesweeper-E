#pragma once

#include "core/exceptions/Exceptions.h"


#include "core/ecs/ECS.h"

#include "Component.h"
#include "rendering/objects/Sprite.h"

#include "input/eventhandler/EventHandler.h"
#include "rendering/SDLwrappers/Rendering_Wrappers.h"


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

	

	//the purpose of this system is to be a more cache_friendly approach to the Spr_system
	class Sprite_System : public Empaerior::System
	{
	public:
	
	
		size_t emplace_sprite(Empaerior::ECS& ecs, const Empaerior::u_inter& id,
			const Empaerior::Float_Rect& m_rect, 
			const Empaerior::Int_Rect& m_tex_rect, 
			const Empaerior::string& tex_path 
			)
		{

			size_t index = sprites.push_back({});

			//make the default animation
			size_t animation_index = animations.push_back({ m_tex_rect });
			
			//set the default animation chain
			sprites.objects[index].animation_begin = animation_index;
			sprites.objects[index].cur_frame = animation_index;//end it , it only has one frame
			sprites.objects[index].animation_end = animation_index;//


			//set the next frame in the animation, 
			//in this case , as we only load one frame, the next frame is actually the current frame
			animations.objects[animation_index].next_animation = animation_index;
			sprites.objects[index].default_anim_frame = animation_index;
			
			Empaerior::SpriteFunctions::InitSprite(sprites.objects[index], m_rect, tex_path);


			
			ecs.get_component<Empaerior::Sprite_Component>(id).all_sprite_index.push_back(index);
	
		
			std::cout << sprites.objects.size() << ' ' << sprites.freed_indexes.size() << '\n';
			return index;

		}

		size_t emplace_textsprite( Empaerior::ECS& ecs, const Empaerior::u_inter& id,
			const Empaerior::Float_Rect& m_rect,
			const Empaerior::string& font_path, 
			const Empaerior::u_int& m_size,
			const Empaerior::string& message,
			Empaerior::Color m_color)
		{
			size_t index = sprites.push_back({});
			size_t animation_index = animations.push_back({ {0,0,static_cast<Empaerior::s_int>(m_rect.dimensions.w),static_cast<Empaerior::s_int>(m_rect.dimensions.h) } });
			//set the next frame in the animation, 
			//in this case , as we only load one frame, the next frame is actually the current frame
			animations.objects[animation_index].next_animation = animation_index;
			sprites.objects[index].default_anim_frame = animation_index;

			Empaerior::SpriteFunctions::InitTextSprite(sprites.objects[index], m_rect, font_path, m_size, message, m_color);

			//set the default animation chain
			sprites.objects[index].animation_begin = animation_index;
			sprites.objects[index].cur_frame = animation_index;//end it , it only has one frame
			sprites.objects[index].animation_end = animation_index;//

		
			ecs.get_component<Empaerior::Sprite_Component>(id).all_sprite_index.push_back(index);

			
			
			return index;
		
		}


		void update(Empaerior::ECS& ecs, const Empaerior::u_int& dt);
		void render(Empaerior::ECS& ecs, Empaerior::Camera& camera);
		 

		//adds another frame to the animation chain of the sprite
		//index - the index of the sprite in the system's vector
		//a method to get the index is by using the index vector of the sprite_component;

		

		//creates a frame and returns the index that frame in the animation vector  
		void create_animation(Empaerior::Sprite_Component::Animation_Entry& entry,Empaerior::Int_Rect frame)
		{
			
			size_t animation_index = animations.push_back({ frame });
			//make the next frame this frame
			animations.objects[animation_index].next_animation = animation_index;

			entry.anim_begin = animation_index;
			entry.anim_end = animation_index;

		

		}
		//appends the frame to the end of the animation
		size_t append_frame(Empaerior::Sprite_Component::Animation_Entry& entry, Empaerior::Int_Rect frame)
		{
			//create a new frame
			size_t new_anim = animations.push_back({ {frame}, });
			//set the last frame to repeat indefinetely
			animations.objects[new_anim].next_animation = new_anim;
			//put the animation in the chain
			animations.objects[entry.anim_end].next_animation = new_anim;
			entry.anim_end = new_anim;

			return new_anim;

		}

		void delete_animation(Empaerior::Sprite_Component::Animation_Entry& entry)
		{
			//stack
			std::set<size_t> to_free;
			//insert the first
			to_free.insert(entry.anim_begin);
			//keep the next
			size_t next = animations.objects[entry.anim_begin].next_animation;

			//while the end isn't reached
			//loop the chain
			while (to_free.find(next) == to_free.end())
			{
				//insert the next
				to_free.insert(next);
				//go to the next
				next = animations.objects[next].next_animation;
			}
			//delete all in the chain
			for (const auto& a : to_free)
			{
				animations.remove(a);
			}



		}

		//makes the animation chain loop
		EMP_FORCEINLINE void make_animation_loop(Empaerior::Sprite_Component::Animation_Entry& entry)
		{
			
			animations.objects[entry.anim_end].next_animation = entry.anim_begin;

		}

		void set_sprite_animation(Empaerior::u_inter sprite_id,Empaerior::Sprite_Component::Animation_Entry& entry)
		{
			sprites.objects[sprite_id].animation_begin = entry.anim_begin;
			sprites.objects[sprite_id].cur_frame = entry.anim_begin;
			sprites.objects[sprite_id].animation_end = entry.anim_end;
		}
		//remove the sprites and animations
		void OnEntityRemovedfromSystem(Empaerior::ECS* ecs, const Empaerior::u_inter& entity_id) override
		{
			//for all sprites
			for (auto& sprite : ecs->get_component<Empaerior::Sprite_Component>(entity_id).all_sprite_index)
			{
				//remove the default frame
				animations.remove(sprites.objects[sprite].default_anim_frame);
				//remove the sprite
				sprites.remove(sprite);
			}
			//delete all animations
			for (auto& animations : ecs->get_component<Empaerior::Sprite_Component>(entity_id).animation_index.objects)
			{
				delete_animation(animations);
			}

		}
		
		//deletes both sprites and textsprites
		void delete_sprite(size_t sprite_id)
		{
			//remove the default  animation
			animations.remove(sprites.at(sprite_id).default_anim_frame);
			//removethe sprite
			sprites.remove(sprite_id);
		}

		//

		Empaerior::Graphic_element& get_sprite(size_t index)
		{
			return sprites.at(index);
		}

		

		//all sprites		
		unsafe_vector<Empaerior::Graphic_element> sprites;
		unsafe_vector<Animation> animations;



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