#include "AssetManager.h"
#include "Game.h"
#include  <string>
#include <iostream>
std::shared_ptr<SDL_Texture> assetManager::load_texture(const std::string& tex_path)
{
	
		//search for texture
		auto tex = Textures.find(tex_path);
		if (tex == Textures.end())
		{
			try {
				//if not found create the texture		
				SDL_RWops* rwop;

				if (!(rwop = SDL_RWFromFile(tex_path.c_str(), "rb"))) // if the file doesn't exists throws exception
				{
					//not very nice method to make the string
					std::string message = "File not found, exception at ";
					message += __FILE__;
					message += " at line ";
					message += std::to_string(__LINE__);

					throw std::invalid_argument(message);
					
				}



				if (IMG_isPNG(rwop))  // if the  image is a good png
				{
					//create atextureand free the rwop
					std::shared_ptr<SDL_Texture> tex_p = sdl_shared(IMG_LoadTextureTyped_RW(Game::renderer, rwop, 1, "PNG"));

					Textures.insert({ tex_path,tex_p });  // put texture in  map

					return tex_p;
				}
				else
				{

					//delete rwop
					SDL_RWclose(rwop);
					//send the exception
					std::string message = "File is not a valid PNG, exception at ";
					message += __FILE__;
					message += " at line ";
					message += std::to_string(__LINE__);
					throw std::invalid_argument(message);

				}


			}
			catch (const std::invalid_argument & e) {
					// do stuff with exception... 
				    std::cout << e.what() << '\n';
					//return a nullpointer
					return nullptr;
			}

	
		}
		else
		{

			//if found 
			return tex->second;

		}
	
	

}

TTF_Font* assetManager::load_font(const std::string& font_path,const int& size)
{
	//this was a fucking rollercoaster
	//I hope I never have to do this ever again
	//search for good font
	
	auto f_name = Fonts.find(font_path);//search for font map
	if (f_name == Fonts.end())
	{
		
		//create font ( and font) map and put in the font
		Fonts.insert({ font_path,std::move(std::map<int,std::unique_ptr<TTF_Font>>()) });
		std::unique_ptr<TTF_Font> fnt = std::unique_ptr<TTF_Font>(TTF_OpenFont(font_path.c_str(),size));
		
		

		Fonts[font_path].insert({ size,std::move(fnt) });
	
		return &(*Fonts[font_path][size]);
	}
	else
	{
		//if there is a map with the font name
		auto size_find = Fonts[font_path].find(size);
		if (size_find == Fonts[font_path].end())
		{
			std::unique_ptr<TTF_Font> fnt = std::unique_ptr<TTF_Font>(TTF_OpenFont(font_path.c_str(), size));
			Fonts[font_path].insert({ size,std::move(fnt) });
			//std::cout << "loaded new size for font" << '\n';
		
			return &(*Fonts[font_path][size]);
		}
		else
		{
			//if there's a font found
			//std::cout << "found a font" << '\n';
			return &(*size_find->second);
		}

	}
}

void assetManager::play_sound(const std::string& sound_path)
{
	auto sound = Sounds.find(sound_path);
	if (sound == Sounds.end())// not found, create new one
	{
		

		std::unique_ptr<Mix_Chunk>TempSound = std::unique_ptr<Mix_Chunk>(Mix_LoadWAV(sound_path.c_str()));
	
		Sounds.insert({sound_path,std::move(TempSound)});
		Mix_PlayChannel(-1, &(*Sounds[sound_path]), 0);
	}
	else
	{
		Mix_PlayChannel(-1, &(*sound->second) , 0);
	}
}


void assetManager::clean_textures()
{
	
	for (auto i = Textures.begin(); i != Textures.end(); )
	{
		
		if (i->second.use_count() == 1)
		{
			
			i = Textures.erase(i);
		}
		else
		{
			++i;
		}
	}

}

void assetManager::clear_fonts()
{
	Fonts.clear();
}
