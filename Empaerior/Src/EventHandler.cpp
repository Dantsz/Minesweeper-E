#include "EventHandler.h"

void Empaerior::EventListener::register_event(Uint32 type, EventCallback callback)
{
	_registeredCallbacks[type].push_back(callback);
}


void Empaerior::EventListener::handleEvents(const SDL_Event& cur_event)
{
	for (int i = 0; i < _registeredCallbacks[cur_event.type].size(); i++)//iterate throught command and match thoose that fit
	{
		_registeredCallbacks[cur_event.type][i](cur_event);
	}

}
