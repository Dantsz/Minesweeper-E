#pragma once
#include "../../ECS.h"
#include "../system.h"
#include "../../components/Component.h"
class Mine_sweep_system : public Empaerior::System
{
public:
	//reveal a cell
	void Reveal(Empaerior::ECS& ecs,const uint64_t& entity_id, int x, int y)
	{
	
	#define tile ecs.get_component<Mine_field>(entity_id).field[x][y]
	
		
		if (ecs.get_component<field_component>(tile).field_type == 0)
		{
			//remove the cell

			//this line is not elegant at all
			if (!ecs.get_component<cell_component>(tile).is_revealed)
			{
				ecs.get_component<cell_component>(tile).is_revealed = true;
				ecs.get_component<Empaerior::Sprite_Component>(tile).sprites.pop_back();
				if (x + 1 < 16) Reveal(ecs, entity_id, x + 1, y);
				if (y + 1 < 16) Reveal(ecs, entity_id, x, y + 1);
				if (x - 1 >= 0)	Reveal(ecs, entity_id, x - 1, y);
				if (y - 1 >= 0) Reveal(ecs, entity_id, x, y - 1);
				if (x + 1 < 16 && y + 1 < 16)  Reveal(ecs, entity_id, x + 1, y + 1);
				if (x + 1 < 16 && y - 1 >= 0)  Reveal(ecs, entity_id, x + 1, y - 1);
				if (x - 1 >= 0 && y - 1 >= 0)  Reveal(ecs, entity_id, x - 1, y - 1);
				if (x - 1 >= 0 && y + 1 < 16)  Reveal(ecs, entity_id, x - 1, y + 1);
			}
			
			

		}
		else
		{
			if (!ecs.get_component<cell_component>(tile).is_revealed)
			{
				ecs.get_component<cell_component>(tile).is_revealed = true;
				ecs.get_component<Empaerior::Sprite_Component>(tile).sprites.pop_back();
			}
		}



	#undef tile
	}





};