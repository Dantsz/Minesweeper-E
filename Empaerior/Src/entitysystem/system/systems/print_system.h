#pragma once
#include "../../ECS.h"
#include "../../system/system.h"
#include "../../components/Component.h"

class Print_System : public Empaerior::System
{
public:

	void update(Empaerior::ECS& ecs)
	{
		for (auto const& e : entities_id)
		{
			std::cout <<  ecs.get_component<Empaerior::Print_Component>(e).message << '\n';
		}
	}

};