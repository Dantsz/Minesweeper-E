#pragma once
#include <unordered_map>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "../graphics/glyphs/Glyphs.h"






/*Singleton class*/

class assetManager
{
public:
	//texture
	static std::shared_ptr<SDL_Texture>  load_texture(const std::string& tex_path);
	//font
	static TTF_Font* load_font(const std::string& font_path, const int& size);

	//sound   
	static void play_sound(const std::string& sound_path);
	static void set_volume(const int n_volume);






	//clear ununsed
	static void clean_textures();
	//clear all
	static void clear_textures();
	static void clear_fonts();
	static void clear_sounds();
	



	static void reset_assets();

public:
static std::unordered_map<std::string,std::shared_ptr<SDL_Texture>> Textures;
static std::unordered_map<std::string,std::unordered_map<int, std::unique_ptr<TTF_Font>>> Fonts;
static std::unordered_map<std::string, std::unique_ptr<Mix_Chunk>> Sounds;
};