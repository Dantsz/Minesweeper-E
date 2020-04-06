#pragma once
#include <Empaerior.h>
#define board_size 16


struct Mine_field
{
	//the field of entities
	Empaerior::u_inter field[board_size][board_size];
	Empaerior::boole mine_encountered = 0;
	Empaerior::u_inter free_spaces = 0;
	//spaces that need to be equlaed in order to win
	Empaerior::u_inter all_spaces = 0;
	//number of flags
	Empaerior::u_inter flags = 0;

};

struct cell_component
{
	//0 - normal cell
	//1 - flag cell
	//2 - ? cell
	Empaerior::u_inter cell_type;
	Empaerior::boole is_revealed;
	Empaerior::boole is_clicked;
};



struct field_component
{
	//-1 bomb
	//0- empty
	//n - n field , n <= 8
	Empaerior::u_inter field_type;
};


class Mine_sweep_system : public Empaerior::System
{
public:
	//reveal a cell
	void Reveal(Empaerior::ECS& ecs,std::shared_ptr<Empaerior::Sprite_System>& Spr_system, const uint64_t& entity_id, int x, int y);
	Empaerior::u_inter get_nr_cell(Empaerior::ECS& ecs, const uint64_t& entity_id)
	{
		Empaerior::u_inter nr = 0;
		for (int i = 0; i < board_size; i++)
		{
			for (int j = 0; j < board_size; j++)
			{
#define tile ecs.get_component<Mine_field>(entity_id).field[i][j]
				if (ecs.get_component<field_component>(tile).field_type >= 0 && ecs.get_component<cell_component>(tile).is_revealed)
				{
					nr++;
#undef tile
				}

			}
		}
		return nr;
	}
	
};
