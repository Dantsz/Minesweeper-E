#include "Sprite.h"
#include "Game.h"
#include "Glyphs.h"
void Sprite::draw(const Camera& camera)
{
	SDL_Rect position_rect = {rect.x - camera.rect.x,rect.y - camera.rect.y,rect.w,rect.h };
	SDL_RenderCopyEx(Game::renderer, &(*texture), &tex_rect, &position_rect, angle, NULL, SDL_FLIP_NONE);
}
void Text_Sprite::draw(const Camera& camera)
{
	
	renderLine(text_values, rect.x, rect.y , glyphs, Game::renderer, rect.w, rect.h,angle,camera.rect.x,camera.rect.y);

}




Text_Sprite::Text_Sprite(const SDL_Rect& rect, const std::string& font_path, const unsigned int& size, const std::string& message,  SDL_Color& color)
	:Graphic_element(rect) // no use for tex_ rect
{

	createGlyphs(this->glyphs,font_path,size, Game::renderer, color); // create glyphs
	text_values = load_glyph_values(message);//translate the message to glyph values
}             
   
      