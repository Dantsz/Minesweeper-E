

#pragma once
#include <memory>
#include <SDL.h>

/*
**Wraps poniters to basic sdl structs in std::unique_ptr and std::shated_ptr*/

//default destructor for unique ptr	
namespace std {
	template<>
	struct std::default_delete<SDL_Texture> {
		void operator()(SDL_Texture* p) { SDL_DestroyTexture(p); }
	};
	template<>
	struct std::default_delete<TTF_Font> {
		void operator()(TTF_Font* p) { TTF_CloseFont(p); }
	};


}

//smart destructor for shared ptr
struct SDL_Del
{

	static void SDL_DelRes(SDL_Window* r) { SDL_DestroyWindow(r); }
	static void SDL_DelRes(SDL_Renderer* r) { SDL_DestroyRenderer(r); }
	static void SDL_DelRes(SDL_Texture* r) { SDL_DestroyTexture(r); }
	static void SDL_DelRes(SDL_Surface* r) { SDL_FreeSurface(r); }
};

template <typename T>
//creates a shared ptr with the specified destructor`
std::shared_ptr<T> sdl_shared(T* t) {
	return std::shared_ptr<T>(t, [](T* t) { SDL_Del::SDL_DelRes(t); });
}
