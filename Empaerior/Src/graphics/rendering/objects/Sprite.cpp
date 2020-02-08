#include "pch.h"
#include "Sprite.h"
#include "../../../Application.h"
#include "../../glyphs/Glyphs.h"
#include "../Window.h"
#include "SDLwrappers/Rendering_Wrappers.h"

void Empaerior::Sprite::Init(const Empaerior::Float_Rect& m_rect, const Empaerior::Int_Rect& m_tex_rect, const Empaerior::string& tex_path, const  Empaerior::byte& m_frames)
{
	path = tex_path;
	rect = m_rect;
	tex_rect = m_tex_rect;
	// load the texture
	texture = Asset_Loading::load_texture(tex_path);
	frames = m_frames;

}


//TODO: change to use float in rendering
void Empaerior::Sprite::draw(const Camera& camera)
{
	Empaerior::Float_Rect_S position_rect = {rect.dimensions.x - camera.rect.x,rect.dimensions.y - camera.rect.y,rect.dimensions.w,rect.dimensions.h };
	if (texture != nullptr)
	{
		//setting the texture's color, because each sprite that uses the texture uses it differently (or not)
		SDL_SetTextureColorMod(texture.get(), r, g, b);//Safe/acceptable to call SDL_SetTextureColorMod a lot?
		//render it
		Empaerior::Render::RenderEx(Application::window.renderer, &(*texture), &tex_rect, &position_rect, rect.angle, NULL, SDL_FLIP_NONE);
	}
	
}
Empaerior::Float_Rect& Empaerior::Sprite::get_rect()
{  
	return rect;
}
void Empaerior::Text_Sprite::draw(const Camera& camera)
{
	 
	if(!glyphs.empty())renderLine(text_values, rect.dimensions.x, rect.dimensions.y , glyphs, Application::window.renderer, rect.dimensions.w, rect.dimensions.h,rect.angle,camera.rect.x,camera.rect.y);

}



void Empaerior::Text_Sprite::Init(const Empaerior::Float_Rect& m_rect, const Empaerior::string& font_path, const unsigned int& size, const Empaerior::string& message, Empaerior::Color& color)
{
	rect = m_rect;
	if (createGlyphs(this->glyphs, font_path, size, Application::window.renderer, color) != -1)// create glyphs
	{
		text_values = load_glyph_values(message);//translate the message to glyph values
	}
}
      