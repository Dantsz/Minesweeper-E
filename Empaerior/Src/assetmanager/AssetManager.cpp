#include "pch.h"
#include "AssetManager.h"
#include "../Game.h"
#include "../SDLwrappers/Ptr_Wrappers.h"
#include "../Exceptions/Exceptions.h"


extern std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Textures;
extern std::unordered_map<std::string, std::unordered_map<int, std::unique_ptr<TTF_Font>>> Fonts;
extern std::unordered_map<std::string, std::unique_ptr<Mix_Chunk>> Sounds;

namespace Empaerior::Asset_Loading
{

	std::shared_ptr<SDL_Texture> load_texture(const std::string& tex_path)//returnsnullptr on  exception
	{
		//I Had to rewrite this whole fucking things so please don't have leaks....
		//search for texture
		auto tex = Textures.find(tex_path);
		if (tex == Textures.end())
		{
			try {
				//if not found create the texture		
				SDL_RWops* rwop;
				rwop = SDL_RWFromFile(tex_path.c_str(), "rb");
				if (rwop == nullptr) // if the file doesn't exists throws exception
				{

					throw E_runtime_exception("File not found", __FILE__, __LINE__);

				}



				if (IMG_isPNG(rwop))  // if the  image is a good png
				{
					//create atextureand free the rwop
					std::shared_ptr<SDL_Texture> tex_p = sdl_shared(IMG_LoadTextureTyped_RW(Empaerior::Game::window.renderer, rwop, 1, "PNG"));

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
			catch (E_runtime_exception & e) {
				// do stuff with exception... 
				e.print_message();
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

	TTF_Font* load_font(const std::string& font_path, const int& size)
	{
		//this was a fucking rollercoaster
		//I hope I never have to do this ever again
		//search for good font
		try {
			auto f_name = Fonts.find(font_path);//search for font map
			if (f_name == Fonts.end())
			{

				//create font ( and font) map and put in the font
				Fonts.insert({ font_path,std::move(std::unordered_map<int,std::unique_ptr<TTF_Font>>()) });


				SDL_RWops* rwop = SDL_RWFromFile(font_path.c_str(), "rb");
				if (rwop == nullptr) // if the file doesn't exists throws exception
				{

					throw E_runtime_exception("File not found", __FILE__, __LINE__);

				}
				std::unique_ptr<TTF_Font> fnt = std::unique_ptr<TTF_Font>(TTF_OpenFontRW(rwop, 1, size));
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

					SDL_RWops* rwop = SDL_RWFromFile(font_path.c_str(), "rb");
					if (rwop == nullptr) // if the file doesn't exists throws exception
					{

						throw E_runtime_exception("File not found", __FILE__, __LINE__);

					}
					std::unique_ptr<TTF_Font> fnt = std::unique_ptr<TTF_Font>(TTF_OpenFontRW(rwop, 1, size));
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
		catch (E_runtime_exception & e) {
			// do stuff with exception... 
			e.print_message();
			//return a nullpointer
			return nullptr;
		}

	}

	void play_sound(const std::string& sound_path)
	{
		try {
			auto sound = Sounds.find(sound_path);
			if (sound == Sounds.end())// not found, create new one
			{

				SDL_RWops* rwop;
				rwop = SDL_RWFromFile(sound_path.c_str(), "rb");
				//load the sound in the rwop
				//Mix_LoadWAV(sound_path.c_str())
				if (rwop == nullptr)
				{
					throw E_runtime_exception("Cannot .wav find file ", __FILE__, __LINE__);
				}
				std::unique_ptr<Mix_Chunk>TempSound = std::unique_ptr<Mix_Chunk>(Mix_LoadWAV_RW(rwop, 1));

				Sounds.insert({ sound_path,std::move(TempSound) });
				Mix_PlayChannel(-1, &(*Sounds[sound_path]), 0);

			}
			else
			{
				Mix_PlayChannel(-1, &(*sound->second), 0);
			}
		}
		catch (E_runtime_exception & e) {
			// do stuff with exception... 
			e.print_message();
		}
	}

	void set_volume(const int n_volume)
	{
		Mix_Volume(-1, n_volume);
	}


	void clean_textures()
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

	void clear_fonts()
	{

		Fonts.clear();
	}

	void clear_sounds()
	{
		for (auto i = Sounds.begin(); i != Sounds.end();)
		{

			i->second.reset();
			Sounds.erase(i);
			if (Sounds.empty()) return;
		}

		Sounds.clear();
	}
	


	void clear_textures()
	{
		if (Textures.empty()) return;
		for (auto i = Textures.begin(); i != Textures.end();)
		{

			i->second.reset();
			i = Textures.erase(i);
			if (Textures.empty()) return;
		}

		Textures.clear();
	}

	void reset_assets()
	{
		Asset_Loading::clear_textures();
		Asset_Loading::clear_fonts();//clear all fonts so TTF_Quit doesn't throw an exceptions
		Asset_Loading::clear_sounds();

	}

	
}