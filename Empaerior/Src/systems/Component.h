#pragma once
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "rendering/Camera.h"
#include "rendering/objects/Sprite.h"

#include "eventhandler/EventHandler.h"

namespace Empaerior
{


	
	/*
	New Sprite Component
	*/
	struct Spr_Component
	{
		//the order in which sprites are drawn
		Empaerior::vector<size_t> spr_index;
		Empaerior::vector<Empaerior::Graphic_element> sprites;
		//indexes for sprites that are deleted 
		Empaerior::queue<size_t> freed_indexes;
	};


	struct Event_Listener_Component
	{ 
		Event_Listener event_listener;
	};


	//Timed Exceution Component
	struct T_E_Component
	{
		//the function
		using Timed_Function = std::function<void()>;
		//times passes
		Empaerior::vector<Empaerior::u_inter> elapsed_time;
		//the total time
		Empaerior::vector<Empaerior::u_inter> time;
		//function container	
		Empaerior::vector<Timed_Function> functions;
		//the times the functions is to be called
		Empaerior::vector<Empaerior::s_inter> call_times;
	};


}