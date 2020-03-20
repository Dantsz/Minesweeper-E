#pragma once

#include <string>
#include <iostream>
#include <Empaerior.h>
#include <cmath>
#include "core/defines/Defines.h"
namespace Empaerior
{
	namespace Utilities {
		//clipboard functions

		Empaerior::string get_clipboard_text();

		 void set_clipboard_text(const char* text);




		//system functions
		 EMP_FORCEINLINE Empaerior::string get_platform()//gets the current platform
		{
			const char* sdl_platform = SDL_GetPlatform();
			Empaerior::string e_platform = sdl_platform;
			SDL_free((void*)sdl_platform);
			return e_platform;

		}

		 EMP_FORCEINLINE int cpu_cache_size()// returns the size of the cpu  cache in bytes
		{
			return SDL_GetCPUCacheLineSize();
		}
		
		 EMP_FORCEINLINE int get_core_number()// get the number of CPU cores available
		{
			return SDL_GetCPUCount();
		}
		 EMP_FORCEINLINE int get_system_ram()//get the amount of RAM configured in the system.
		{
			return SDL_GetSystemRAM();
		}



		//check if a rect contains a point
		Empaerior::boole rect_contains_point(const Empaerior::Float_Rect& rect, Empaerior::fl_point x , Empaerior::fl_point y);
		Empaerior::boole rect_contains_point(const Empaerior::Float_Rect& rect,const Empaerior::Point2f point);


	}

	



}