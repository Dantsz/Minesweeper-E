#pragma once
#include <Empaerior.h>



struct Mine_field
{
	//the field of entities
	Empaerior::u_inter field[16][16];

}; 

struct cell_component
{
	//0 - normal cell
	//1 - flag cell
	//2 - ? cell
	Empaerior::u_inter cell_type;
	Empaerior::boole is_revealed;
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
	void Reveal(Empaerior::ECS& ecs, const uint64_t& entity_id, int x, int y);
};