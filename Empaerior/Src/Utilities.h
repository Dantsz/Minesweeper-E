#pragma once
#include <SDL.h>
#include <string>
namespace Empaerior
{
	std::string get_clipboard_text()
	{
		if (SDL_HasClipboardText)//if there's text
		{
			char* sdl_text = SDL_GetClipboardText();//get the clipboard content as char*
			std::string clip_text = sdl_text;//transfom  the char* intoa std::string
			SDL_free(sdl_text);//free the char*
			return clip_text;//return a string
		}
		return "";
	}

	void set_clipboard_text(const char* text)
	{
		try
		{
			if (SDL_SetClipboardText(text) < 0)
			{
				throw E_runtime_exception("Cannot copy text to clipboard",__FILE__,__LINE__);
			}
		}
		catch (const E_runtime_exception & e) {
			
			std::cout << e.what() << '\n';
			return;
		}
	}






}