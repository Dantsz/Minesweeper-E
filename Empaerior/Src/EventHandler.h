#pragma once
#include <SDL.h>
#include<SDL_events.h>
#include <map>
#include <functional>

namespace Empaerior {


	//stack overflow to the rescue
	class EventListener//handles only one type of SDL_event
	{
	public:

		using EventCallback = std::function<void(SDL_Event const&)>;

		EventListener() {};
		~EventListener() {};


		void register_event(Uint32 type, EventCallback callback) //put a callback in the lisener
		{
			_registeredCallbacks[type].push_back(callback);
		}

		void handleEvents(const SDL_Event& cur_event) //execute commands
		{
			for (int i = 0; i < _registeredCallbacks[cur_event.type].size(); i++)//iterate throught command and match thoose that fit
			{
				_registeredCallbacks[cur_event.type][i](cur_event);
			}

		}

	private:
		std::map<Uint32, std::vector<EventCallback>> _registeredCallbacks;//type of the event and function
	};
}

