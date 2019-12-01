#pragma once
#include <map>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "Glyphs.h"






/*Singleton class*/

class assetManager
{
public:

	static std::shared_ptr<SDL_Texture>  load_texture(const std::string& tex_path);
	static TTF_Font* load_font(const std::string& font_path, const int& size);
	static void play_sound(const std::string& sound_path);




	static void clean_textures();


private:
static std::map<std::string,std::shared_ptr<SDL_Texture>> Textures;
static std::map<std::string,std::map<int, std::unique_ptr<TTF_Font>>> Fonts;

static std::map<std::string, Mix_Chunk*> Sounds;
};