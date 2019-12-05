#include "Window.h"

Window::Window(const std::string& name, const Uint32& width, const Uint32& height)
: width(width),height(height)
{
	window = SDL_CreateWindow(name.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, 0);
}

Window::Window()
{
}

int Window::Init(const std::string& name, const Uint32& m_width, const Uint32& m_height)
{
	width = m_width;
	height = m_height;
	window = SDL_CreateWindow(name.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, 0);

	return 0;
}

void Window::render()
{
	SDL_RenderPresent(renderer);
}

void Window::clear()
{
	SDL_RenderClear(renderer);
}

void Window::reset()
{
	if (window != nullptr)	SDL_DestroyWindow(window);
	if (renderer != nullptr)SDL_DestroyRenderer(renderer);
}

void Window::toggle_fullscreen()
{
	Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
	bool IsFullscreen = SDL_GetWindowFlags(window) & FullscreenFlag;
	SDL_SetWindowFullscreen(window, IsFullscreen ? 0 : FullscreenFlag);
}
