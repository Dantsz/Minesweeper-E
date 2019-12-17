#include "pch.h"
#include "Sprite.h"
#include "../../../Game.h"
#include "../../glyphs/Glyphs.h"
#include "../Window.h"


void Empaerior::Sprite::draw(const Camera& camera)
{
	SDL_Rect position_rect = {rect.x - camera.rect.x,rect.y - camera.rect.y,rect.w,rect.h };
	if(texture != nullptr)SDL_RenderCopyEx(Game::window.renderer, &(*texture), &tex_rect, &position_rect, angle, NULL, SDL_FLIP_NONE);
}
void Empaerior::Text_Sprite::draw(const Camera& camera)
{
	
	if(!glyphs.empty())renderLine(text_values, rect.x, rect.y , glyphs, Game::window.renderer, rect.w, rect.h,angle,camera.rect.x,camera.rect.y);

}




Empaerior::Text_Sprite::Text_Sprite(const SDL_Rect& rect, const std::string& font_path, const unsigned int& size, const std::string& message,  SDL_Color& color)
	:Graphic_element(rect) // no use for tex_ rect
{
	if (createGlyphs(this->glyphs, font_path, size, Game::window.renderer, color) != -1)// create glyphs
	{
		
		text_values = load_glyph_values(message);//translate the message to glyph values
	}
}             
   
      