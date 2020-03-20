#include "pch.h"
#include "Sprite.h"
#include "Application.h"
#include "rendering/glyphs/Glyphs.h"
#include "../Window.h"
#include "../SDLwrappers/Rendering_Wrappers.h"



void Empaerior::Graphic_element::draw(const Camera& camera)
{
	position_rect = { rect.dimensions.x - camera.rect.x,rect.dimensions.y - camera.rect.y,rect.dimensions.w,rect.dimensions.h };
	//setting the texture's color, because each sprite that uses the texture uses it differently (or not)
	SDL_SetTextureColorMod(texture.get(), r, g, b);//Safe/acceptable to call SDL_SetTextureColorMod a lot?
	//render it
	Empaerior::Render::RenderEx(Application::window.renderer, &(*texture), SDL_FLIP_NONE, rect.angle, 0, &tex_rect, &position_rect);

}

void Empaerior::SpriteFunctions::InitTextSprite(Empaerior::Graphic_element& spr, const Empaerior::Float_Rect& rect, const Empaerior::string& font_path, const Empaerior::u_int& size, const Empaerior::string& message, Empaerior::Color& color)
{
	spr.rect = rect;
	spr.r = color.r;
	spr.g = color.g;
	spr.b = color.b;
	spr.path = font_path;
	spr.frames = 1;
	Create_text_texture(load_glyph_values(message), rect, *Empaerior::Asset_Loading::load_glyph_vector(font_path, size), Application::window.renderer, spr.texture,spr.tex_rect);
}

void Empaerior::SpriteFunctions::set_message(Empaerior::Graphic_element& spr, const Empaerior::string& message, const Empaerior::s_int& size)
{
	Create_text_texture(load_glyph_values(message), spr.rect, *Empaerior::Asset_Loading::load_glyph_vector(spr.path, size), Empaerior::Application::window.renderer, spr.texture,spr.tex_rect);
}
