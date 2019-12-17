#pragma once
#include <SDL.h>

namespace Empaerior
{


	class Camera
	{
	public:
		Camera()
		{

		}
		~Camera()
		{

		}
		Camera(const SDL_Rect& camera)
			:rect(camera)

		{

		}
		Camera(const int& x, const int& y, const int& w, const int& h)
			:rect({ x,y,w,h })

		{

		}
		void set_position(const int& x, const int& y)
		{
			rect.x = x;
			rect.y = y;

		}
		void set_dimensions(const int& w, const int& h);


		SDL_Rect rect = { 0,0,0,0 };

	private:


	};
}