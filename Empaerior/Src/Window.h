#pragma once
#include <SDL.h>
#include <string>

class Window
{
friend class Game;//Game can edit it's window

public:
	Window();
	Window(const std::string & name,const Uint32& width,const Uint32& height);
	
		
	

	~Window()
	{
		if (window != nullptr)	SDL_DestroyWindow(window);
		if(renderer != nullptr)SDL_DestroyRenderer(renderer);
		
	}
	int Init(const std::string& name, const Uint32& width, const Uint32& height);
	void render();
	void clear();

	void reset();
	void toggle_fullscreen();

	SDL_Renderer* renderer;
	SDL_Window* window;
private:
	

	Uint32 width = 0;
	Uint32 height = 0;
};