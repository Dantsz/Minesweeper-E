#include "Minesweeper.h"

void Mine_sweep_system::Reveal(Empaerior::ECS& ecs, std::shared_ptr<Empaerior::Sprite_System>& Spr_system, const uint64_t& entity_id, int x, int y)
{

#define tile ecs.get_component<Mine_field>(entity_id).field[x][y]

	if (ecs.get_component<cell_component>(tile).cell_type == 0)
	{
		if (ecs.get_component<field_component>(tile).field_type == 0)
		{
			//remove the cell
			
			//this line is not elegant at all
			if (!ecs.get_component<cell_component>(tile).is_revealed)
			{
			
				ecs.get_component<cell_component>(tile).is_revealed = true;
				Spr_system->delete_sprite(ecs.get_component<Empaerior::Sprite_Component>(tile).all_sprite_index[ecs.get_component<Empaerior::Sprite_Component>(tile).all_sprite_index.size() - 1]);
			
				ecs.get_component<Empaerior::Sprite_Component>(tile).all_sprite_index.pop_back();
			
				if (x + 1 < board_size) Reveal(ecs, Spr_system, entity_id, x + 1, y);
				if (y + 1 < board_size) Reveal(ecs, Spr_system, entity_id, x, y + 1);
				if (x - 1 >= 0) Reveal(ecs, Spr_system, entity_id, x - 1, y);
				if (y - 1 >= 0) Reveal(ecs, Spr_system, entity_id, x, y - 1);
				if (x + 1 < board_size && y + 1 < board_size)  Reveal(ecs, Spr_system, entity_id, x + 1, y + 1);
				if (x + 1 < board_size && y - 1 >= 0)  Reveal(ecs, Spr_system, entity_id, x + 1, y - 1);
				if (x - 1 >= 0 && y - 1 >= 0)  Reveal(ecs, Spr_system, entity_id, x - 1, y - 1);
				if (x - 1 >= 0 && y + 1 < board_size)  Reveal(ecs, Spr_system,entity_id, x - 1, y + 1);
			}



		}
		else if (ecs.get_component<field_component>(tile).field_type == -1)
		{
			//IF A MINE HAS BEEN TOUCHED

			ecs.get_component<cell_component>(tile).is_revealed = true;
			//change the texture of touched mine
			Spr_system->get_sprite(ecs.get_component<Empaerior::Sprite_Component>(tile).all_sprite_index[0]).set_texture("assets/tex_mine_cross.png");
			ecs.get_component<Mine_field>(entity_id).mine_encountered = 1;

			//reveal ALL  mines
			for (int i = 0; i < board_size; i++)
			{
				for (int j = 0; j < board_size; j++)
				{
#define it_tile ecs.get_component<Mine_field>(entity_id).field[i][j]
					if (ecs.get_component<field_component>(it_tile).field_type == -1)
					{

						if (ecs.get_component<Empaerior::Sprite_Component>(it_tile).all_sprite_index.size() == 2 && ecs.get_component<cell_component>(it_tile).cell_type == 0)
						{
						
							ecs.get_component<cell_component>(it_tile).is_revealed = 1;
							Spr_system->delete_sprite(ecs.get_component<Empaerior::Sprite_Component>(it_tile).all_sprite_index[ecs.get_component<Empaerior::Sprite_Component>(tile).all_sprite_index.size() - 1]);

							ecs.get_component<Empaerior::Sprite_Component>(it_tile).all_sprite_index.pop_back();


						}
					}
#undef it_tile
				}
			}
		}
		else
		{
			if (!ecs.get_component<cell_component>(tile).is_revealed)
			{
		
				ecs.get_component<cell_component>(tile).is_revealed = true;
				Spr_system->delete_sprite(ecs.get_component<Empaerior::Sprite_Component>(tile).all_sprite_index[ecs.get_component<Empaerior::Sprite_Component>(tile).all_sprite_index.size() - 1]);

				ecs.get_component<Empaerior::Sprite_Component>(tile).all_sprite_index.pop_back();

			}
		}
		
	}


#undef tile
}
