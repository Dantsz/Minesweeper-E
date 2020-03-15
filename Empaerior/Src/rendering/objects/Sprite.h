#pragma once
#include "core/exceptions/Exceptions.h"
#include "assetmanager/assetmanager.h"
#include "../Camera.h"
#include "rendering/glyphs/Glyphs.h"
namespace Empaerior {
	///base  class for sprite elements, practically vritual
	class Graphic_element
	{
	public:


		Graphic_element()
		{
			
		}

		~Graphic_element()
		{

		}
		void draw(const Camera& camera);
	
		void update(const Empaerior::u_int& dt)
		{
			time += dt; // add the time passed

			while (time >= holdTime)// check if the necesarry time passed
			{
				time -= holdTime;
				next_frame(); // advance
			}

		}


		void set_position(const Empaerior::fl_point& x, const Empaerior::fl_point& y)
		{
			rect.dimensions.x = x;
			rect.dimensions.y = y;
			return;
		}


		// the size of the rect is only for one frame of the sprite
	// so the length of the texture should be frames * tex_rect.w
	
		//sets a new texture instead of the old one
		//rect , animation  and position doesn't change
		void set_texture(const Empaerior::string& tex_path)
		{
			texture = Asset_Loading::load_texture(tex_path);
			path = tex_path;

		}
		//changes the color of the texture to the rgb value provided
		//255,255,255 - 
		void set_color_blend(Empaerior::byte p_r, Empaerior::byte p_g, Empaerior::byte p_b)
		{
			r = p_r;
			g = p_g;
			b = p_b;
		}
		//sets the number of frames the sprite should rotate through, 
		//setting m_frames to 0 behaves the same as setting it to 1
		void set_frames(const Empaerior::byte m_frames)
		{
			frames = m_frames;
		}
		//

		//sets the interval between frame updates of the animation
		//in milliseconds
		void set_hold_time(const Empaerior::u_int new_holdTime)
		{
			try {
				//setting new_frames to 0 should logacally result in an infinite loop 
				//as the animation is constantly being updated with no time in between updates
				if (new_holdTime == 0) throw E_runtime_exception("Hold time cannot be zero", __FILE__, __LINE__, __FUNCTION__);
				holdTime = new_holdTime;
			}
			catch (E_runtime_exception& e)
			{
				e.print_message();
				return;
			}
		}

		//gets the dimesnions of the sprite
		Empaerior::Float_Rect& get_rect() { return rect; }
		
		

	private:
		inline void next_frame()// goes to the next frame in the animation 
		{
			// get next frame in animation
			//if cur_frames has been all frames, go to the frame 0
			cur_frame >= frames - 1 ? cur_frame = 0 : ++cur_frame;
			//set the frame
			tex_rect.x = anim_x + cur_frame * tex_rect.w;
			//tex_rect.y = anim_y + cur_frame * tex_rect.h;

		}
	
	public:
		std::shared_ptr<SDL_Texture> texture;
		//it's the tecture path for sprites and font_path dor text_sprites;
		Empaerior::string path;// the path

		Empaerior::Int_Rect tex_rect;// the portion of the texture the sprite represents
		Empaerior::u_int anim_x = 0, anim_y = 0;//the unaltered positions of the texture with the initial position 

		Empaerior::u_int time = 0;
		Empaerior::u_int holdTime = 250; //time between animations currently 0.25 seconds

		Empaerior::byte frames = 1; //each animation must have at least one frame
		Empaerior::byte cur_frame = 0;

		//color values
		Empaerior::byte r = 255;
		Empaerior::byte g = 255;
		Empaerior::byte b = 255;

		Empaerior::Float_Rect rect; // the sprite

		//used to calculate the position relative to the camera
		Empaerior::Float_Rect_S position_rect;

	};

	

	namespace SpriteFunctions
	{
		inline void set_angle(Empaerior::Graphic_element& spr,const Empaerior::fl_point& newAngle)
		{
			spr.rect.angle = newAngle;
		}

		inline void set_position(Empaerior::Graphic_element& spr,const Empaerior::fl_point& x, const Empaerior::fl_point& y)
		{
			spr.rect.dimensions.x = x;
			spr.rect.dimensions.y = y;
			return;
		}
		inline void set_position(Empaerior::Graphic_element& spr,const Empaerior::Point2f& point)
		{
			spr.rect.dimensions.x = point.x;
			spr.rect.dimensions.y = point.y;
			return;
		}
		//Initialize as a normal sprite 
		inline void InitSprite(Empaerior::Graphic_element& spr,const Empaerior::Float_Rect& m_rect, const Empaerior::Int_Rect& m_tex_rect, const Empaerior::string& tex_path, const Empaerior::byte& m_frames)
		{
			spr.path = tex_path;
			spr.rect = m_rect;
			spr.tex_rect = m_tex_rect;
			// load the texture
			spr.texture = Asset_Loading::load_texture(tex_path);
			spr.frames = m_frames;
		}

		//Initialize as a Text_Sprite
		void InitTextSprite(Empaerior::Graphic_element& spr, const Empaerior::Float_Rect& rect, const Empaerior::string& font_path, const  Empaerior::u_inter& size, const Empaerior::string& message, Empaerior::Color& color);
	
		//SETS THE MESSAGE
		void set_message(Empaerior::Graphic_element& spr, const Empaerior::string& message, const Empaerior::s_int& size);
		
		//Completely resets every component of the sprite
		inline void resetSPR(Empaerior::Graphic_element& spr)
		{
			spr.texture.reset();
			spr.path = "";
			spr.tex_rect = {};
			spr.anim_x = 0;
			spr.anim_y = 0;
			spr.time = 0;
			spr.holdTime = 250;
			spr.frames = 1;
			spr.cur_frame = 0;
			spr.r = 255;
			spr.g = 255;
			spr.b = 255;
			spr.rect = { {0,0,0,0},0 };
			spr.position_rect = {};
		}
	}



}

