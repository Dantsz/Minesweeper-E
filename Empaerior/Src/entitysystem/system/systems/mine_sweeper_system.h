#pragma once
#include "../../ECS.h"
#include "../system.h"
#include "../../components/Component.h"

class Mine_sweep_system : public Empaerior::System
{
public:
	//reveal a cell
	void Reveal(Empaerior::ECS& ecs, const uint64_t& entity_id, int x, int y);

	void OnDeath();
};