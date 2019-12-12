#pragma once
#include "components/Component.h"
#include <vector>
#include <queue>
namespace Empaerior
{
	class Entity
	{
	public:
		bool active;
		uint64_t id;

	};


	class EnityManager
	{
	public:
		uint64_t add_Entity()//takes a fredor makes a new one if there's no id
		{
			return get_id();
		}
		void delete_entity(const uint64_t & id)//deletes an entity ,removes all components and puts its id in the queue
		{

			//***delete entity's component's (not implemented yet) ***//
			//
			//
			//.................

			//pushthe freed id into the queue
			freed_id.push(id);



		}

		//gets an id that is not used
		uint64_t get_id()
		{
			//if there isn't any idin the queue,create a new one
			if (freed_id.empty())
			{

				return lowest_unallocatedid++;

			}
			else
			{
				//take the id from   the front of the queue
				uint64_t id = freed_id.front();
				//popit
				freed_id.pop();
				return  id;

			}
		}
		

	private:
		//ids that had once an entity but now are 
		std::queue<uint64_t> freed_id;


		//the lowest unallocated id that has not interacted with
		uint64_t lowest_unallocatedid = 0;
	};


}