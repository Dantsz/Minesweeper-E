#include "pch.h"
#include "Utilities.h"
#include <SDL.h>
#include "Math.h"

Empaerior::string Empaerior::Utilities::get_clipboard_text()
{
	if (SDL_HasClipboardText())//if there's text
	{
		char* sdl_text = SDL_GetClipboardText();//get the clipboard content as char*
		Empaerior::string clip_text = sdl_text;//transfom  the char* into a Empaerior::string
		SDL_free(sdl_text);//free the char*
		return clip_text;//return a string
	}
	return "";
}

void Empaerior::Utilities::set_clipboard_text(const char* text)
{
	try
	{
		if (SDL_SetClipboardText(text) < 0)
		{
			throw E_runtime_exception("Cannot copy text to clipboard", __FILE__, __LINE__, __FUNCTION__);
		}
	}
	catch (E_runtime_exception & e) {

		e.print_message();
		return;
	}
}



Empaerior::Point2f Empaerior::Utilities::get_screen_mouse_coords()
{

//Transform for the position of the renderer
//This is in case the viewport  doesn't match the camera (blackboxing)

//get the positions
	Empaerior::v_pair<Empaerior::s_int, Empaerior::s_int> pos;
	Empaerior::Point2f f_pos;


	SDL_GetMouseState(&pos.first, &pos.second);



	f_pos.x = float(pos.first);
	f_pos.y = float(pos.second);



	//Scale down the positions to match the world
	float sx = 0;
	float sy = 0;
	SDL_RenderGetScale(Application::window.renderer, &sx, &sy);

	f_pos.x /= sx;
	f_pos.y /= sy;




	//Transform for the position of the renderer
	Empaerior::Int_Rect renderer_viewport;

	SDL_RenderGetViewport(Application::window.renderer, &renderer_viewport);
	f_pos.x -= renderer_viewport.x;
	f_pos.y -= renderer_viewport.y;


	f_pos.x /= renderer_viewport.w;
	f_pos.y /= renderer_viewport.h;


	return f_pos;
}

Empaerior::Point2f Empaerior::Utilities::get_world_mouse_coords(const Empaerior::Camera& camera)
{
	//get the positions
	Empaerior::v_pair<Empaerior::s_int, Empaerior::s_int> pos;
	Empaerior::Point2f f_pos;


	SDL_GetMouseState(&pos.first, &pos.second);



	f_pos.x = float(pos.first);
	f_pos.y = float(pos.second);



	//Scale down the positions to match the world
	float sx = 0;
	float sy = 0;
	SDL_RenderGetScale(Empaerior::Application::window.renderer, &sx, &sy);

	f_pos.x /= sx;
	f_pos.y /= sy;




	//Transform for the position of the renderer
	Empaerior::Int_Rect renderer_viewport;

	SDL_RenderGetViewport(Empaerior::Application::window.renderer, &renderer_viewport);
	f_pos.x -= renderer_viewport.x;
	f_pos.y -= renderer_viewport.y;

	//Transform the position relative to the camera dimesnions
	f_pos.x *= camera.rect.w;
	f_pos.y *= camera.rect.h;



	f_pos.x /= renderer_viewport.w;
	f_pos.y /= renderer_viewport.h;

	
	
	//Tranform for position
	f_pos.x += camera.rect.x;
	f_pos.y += camera.rect.y;




	 return f_pos;

}

Empaerior::boole Empaerior::Utilities::rect_contains_point(const Empaerior::Float_Rect& rect, Empaerior::fl_point x, Empaerior::fl_point y)
{

	Empaerior::fl_point o_x = rect.dimensions.x + rect.dimensions.w/2;
	Empaerior::fl_point o_y = rect.dimensions.y + rect.dimensions.h/2;


	
	//rotating the point counter-clockwise
	Empaerior::fl_point c_x = o_x +  (x - o_x) * Empaerior::Math::cosd(rect.angle) - (y - o_y) * Empaerior::Math::sind(rect.angle);
	Empaerior::fl_point c_y = o_y +	(y - o_y) * Empaerior::Math::cosd(rect.angle) + (x - o_x) * Empaerior::Math::sind(rect.angle);
	
	//
	

	
	//checking the collision
	if (c_x <= rect.dimensions.x || c_x > rect.dimensions.x + rect.dimensions.w) return false;
	if (c_y <= rect.dimensions.y || c_y > rect.dimensions.y + rect.dimensions.h) return false;

	return true;
}

Empaerior::boole Empaerior::Utilities::rect_contains_point(const Empaerior::Float_Rect& rect, const Empaerior::Point2f point)
{


	Empaerior::fl_point o_x = rect.dimensions.x + rect.dimensions.w / 2;
	Empaerior::fl_point o_y = rect.dimensions.y + rect.dimensions.h / 2;



	//rotating the point counter-clockwise
	Empaerior::fl_point c_x = o_x + (point.x - o_x) * Empaerior::Math::cosd(rect.angle) - (point.y - o_y) * Empaerior::Math::sind(rect.angle);
	Empaerior::fl_point c_y = o_y + (point.y - o_y) * Empaerior::Math::cosd(rect.angle) + (point.x - o_x) * Empaerior::Math::sind(rect.angle);

	//



	//checking the collision
	if (c_x <= rect.dimensions.x || c_x > rect.dimensions.x + rect.dimensions.w) return false;
	if (c_y <= rect.dimensions.y || c_y > rect.dimensions.y + rect.dimensions.h) return false;

	return true;
}

