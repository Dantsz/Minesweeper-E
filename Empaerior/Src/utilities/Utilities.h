#pragma once
#include <SDL.h>
#include <string>
#include <iostream>
#include "graphics/rendering/Camera.h"
#include "Exceptions/Exceptions.h"
namespace Empaerior
{
	//clipboard functions
	inline std::string get_clipboard_text()
	{
		if (SDL_HasClipboardText())//if there's text
		{
			char* sdl_text = SDL_GetClipboardText();//get the clipboard content as char*
			std::string clip_text = sdl_text;//transfom  the char* intoa std::string
			SDL_free(sdl_text);//free the char*
			return clip_text;//return a string
		}
		return "";
	}
	inline void set_clipboard_text(const char* text)
	{
		try
		{
			if (SDL_SetClipboardText(text) < 0)
			{
				throw E_runtime_exception("Cannot copy text to clipboard", __FILE__, __LINE__);
			}
		}
		catch (E_runtime_exception & e) {

			e.print_message();
			return;
		}
	}



	//system functions
	inline std::string get_platform()//gets the current platform
	{
		const char* sdl_platform = SDL_GetPlatform();
		std::string e_platform = sdl_platform;
		SDL_free((void*)sdl_platform);
		return e_platform;

	}

	inline	int cpu_cache_size()//returns the size of the cpu  cache in bytes
	{
		return SDL_GetCPUCacheLineSize();
	}

	inline	int get_core_number()// get the number of CPU cores available
	{
		return SDL_GetCPUCount();
	}

	inline	int get_system_ram()//get the amount of RAM configured in the system.
	{
		return SDL_GetSystemRAM();
	}

	std::pair<float,float> get_world_mouse_coords(const Empaerior::Camera& camera);


}