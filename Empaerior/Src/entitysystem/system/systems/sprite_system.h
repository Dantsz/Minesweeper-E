#pragma once




#include "../../ECS.h"
#include "../../system/system.h"
#include "../../components/Component.h"
#include "../../../graphics/rendering/objects/Sprite.h"

//*requires the entity to have a sprite component

class Sprite_System : public Empaerior::System
{
public:

	//adds a new sprite to the entity
	//doesn't need to be efficient
	void add_sprite(Empaerior::ECS& ecs,const uint64_t& id,Empaerior::Sprite& sprite)
	{
		//search for the entity
		 ecs.get_component<Empaerior::Sprite_Component>(id).sprites.emplace_back(sprite);
	}



	//renders all sprites
	void render(Empaerior::ECS& ecs, Empaerior::Camera& camera)
	{
		for (auto& e : entities_id)
		{
			for (auto& sprs : ecs.get_component<Empaerior::Sprite_Component>(e).sprites )
			{
				sprs.draw(camera);
			}
		}
	}

};