#include "AssetManager.h"
#include "Game.h"
#include  <string>
#include <iostream>
#include "Ptr_Wrappers.h"
#include "Exceptions.h"

std::shared_ptr<SDL_Texture> assetManager::load_texture(const std::string& tex_path)//returnsnullptr on  exception
{
		//I Had to rewrite this whole fucking things so please don't have leaks....
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
					throw E_runtime_exception("File not found", __FILE__, __LINE__);
					
				}



				if (IMG_isPNG(rwop))  // if the  image is a good png
				{
					//create atextureand free the rwop
					std::shared_ptr<SDL_Texture> tex_p = sdl_shared(IMG_LoadTextureTyped_RW(Game::window.renderer, rwop, 1, "PNG"));

					Textures.insert({ tex_path,tex_p });  // put texture in  map

					return tex_p;
				}
				else
				{

					//delete rwop
					SDL_RWclose(rwop);
					//send the exception
					throw E_runtime_exception("File is not a valid PNG", __FILE__, __LINE__);

				}


			}
			catch (const E_runtime_exception & e) {
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
	try {
		auto f_name = Fonts.find(font_path);//search for font map
		if (f_name == Fonts.end())
		{

			//create font ( and font) map and put in the font
			Fonts.insert({ font_path,std::move(std::map<int,std::unique_ptr<TTF_Font>>()) });
			std::unique_ptr<TTF_Font> fnt = std::unique_ptr<TTF_Font>(TTF_OpenFont(font_path.c_str(), size));
			if (fnt == nullptr)//throw exception
			{
	
				throw E_runtime_exception("File is not a valid TTF or does not exist", __FILE__, __LINE__);
			}


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
				
				//std::cout << "loaded new size for font" << '\n';
				if (fnt == nullptr)//throw exception
				{				
					throw E_runtime_exception("File is not a valid TTF or does not exist", __FILE__, __LINE__);

				}
				Fonts[font_path].insert({ size,std::move(fnt) });
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
	catch (const E_runtime_exception & e) {
		// do stuff with exception... 
		std::cout << e.what() << '\n';
		//return a nullpointer
		return nullptr;
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

void assetManager::clear_sounds()
{
	for (auto i = Sounds.begin(); i != Sounds.end();)
	{
		
		i->second.reset();
		Sounds.erase(i);
		if (Sounds.empty()) return;
	}
	
	Sounds.clear();
}

void assetManager::reset_assets()
{
	assetManager::clear_textures();
	assetManager::clear_fonts();//clear all fonts so TTF_Quit doesn't throw an exceptions
	assetManager::clear_sounds();

}

void assetManager::clear_textures()
{
	for (auto i = Textures.begin(); i != Textures.end();)
	{
		
		i->second.reset();
		Textures.erase(i);
		if (Textures.empty()) return;
	}
	
	Textures.clear();
}
