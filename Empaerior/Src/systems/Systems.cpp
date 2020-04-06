#include "Systems.h"
#include "Application.h"
#include "pch.h"
#define COMPONENT ecs.get_component<Empaerior::Sprite_Component>(id)
void Empaerior::Sprite_System::update(Empaerior::ECS& ecs, const Empaerior::u_int& dt)
{
	for (auto& id : entities_id)
	{
		for (auto& spr : COMPONENT.all_sprite_index)
		{
		
			sprites.objects[spr].time += dt; // add the time passed
			while (sprites.objects[spr].time >= sprites.objects[spr].holdTime)// check if the necesarry time passed
			{
				sprites.objects[spr].time -= sprites.objects[spr].holdTime;
				//Advance in the animation
				sprites.objects[spr].cur_frame = animations.objects[sprites.objects[spr].cur_frame].next_animation;

			}

		}



	}
}



void Empaerior::Sprite_System::render(Empaerior::ECS& ecs, Empaerior::Camera& camera)
{
	for (auto& id : entities_id)
	{
		for (auto& spr : COMPONENT.all_sprite_index)
		{


			sprites.objects[spr].position_rect = { sprites.objects[spr].rect.dimensions.x - camera.rect.x, sprites.objects[spr].rect.dimensions.y - camera.rect.y, sprites.objects[spr].rect.dimensions.w, sprites.objects[spr].rect.dimensions.h };
			//setting the texture's color, because each sprite that uses the texture uses it differently (or not)
			SDL_SetTextureColorMod(sprites.objects[spr].texture.get(), sprites.objects[spr].r, sprites.objects[spr].g, sprites.objects[spr].b);//Safe/acceptable to call SDL_SetTextureColorMod a lot?
			//render it
		
			
			Empaerior::Render::RenderEx(
				Application::window.renderer,
				&(*sprites.objects[spr].texture),
				SDL_FLIP_NONE, sprites.objects[spr].rect.angle,
				0, 
				&animations.objects[sprites.objects[spr].cur_frame].rect,
				&sprites.objects[spr].position_rect);

		}


	}

}
#undef COMPONENT
