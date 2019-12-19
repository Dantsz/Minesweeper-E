#pragma once
#include "../../ECS.h"
#include "../../system/system.h"
#include "../../components/Component.h"
#include "eventhandler/EventHandler.h"



//
class Event_System : public Empaerior::System
{
public:

	void add_event_to_entity(Empaerior::ECS& ecs,const uint64_t& entity_id,const Uint32& event_type,std::function<void(SDL_Event const&)> function)
	{
		#define EVENTLISTENER  ecs.get_component<Empaerior::Event_Listener_Component>(entity_id).event_listener

		EVENTLISTENER.register_event(event_type, function);

		#undef EVENTLISTENER
	}


	void handle_events(Empaerior::ECS& ecs ,const SDL_Event& event)
	{
		#define EVENTLISTENER  ecs.get_component<Empaerior::Event_Listener_Component>(entity_id).event_listener
		
		for (auto& entity_id : entities_id)
		{

			EVENTLISTENER.handleEvents(event);
		}

		#undef EVENTLISTENER

	}



};