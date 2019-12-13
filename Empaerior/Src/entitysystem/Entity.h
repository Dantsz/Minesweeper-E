#pragma once
#include "components/Component.h"
#include <vector>
#include <algorithm>
#include "../exceptions/Exceptions.h"
#include<iostream>
//thanks to Austin Morlan for providing a ECS template

namespace Empaerior
{
	
	class Entity
	{
	public:
		bool active = true;
		uint64_t id = 0;
	
	

	};


	class EnityManager
	{
	public:


		Entity add_Entity()//takes a freed or makes a new one if there's no id
		{
			Entity new_ent;
			new_ent.id = get_id();
			return new_ent;
		}


		void delete_entity(const uint64_t & id)//deletes an entity ,removes all components and puts its id in the queue
		{
			try
			{
				if (id > lowest_unallocatedid )
				{
					throw E_runtime_exception("Invalid id for deletion : id doesn't exist", __FILE__, __LINE__);

				} 
				//if the id appears in the delted entities
				else if(std::binary_search(freed_id.begin(),freed_id.end(),id))
				{
					throw E_runtime_exception("Invalid id deletion : id is not a valid entity", __FILE__, __LINE__);
				
				}




				//***delete entity's component's (not implemented yet) ***//
				//
				//
				//.................

				//pushthe freed id into the queue


				freed_id.push_back(id);
				//the vector is always sorted in order to check if id apears in it using binary search
				std::sort(freed_id.begin(), freed_id.end());
			}
			catch(E_runtime_exception& e)
			{
				std::cout << e.what() << '\n';
			}


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
				freed_id.pop_back();
				return  id;

			}
		}
		

	private:
		//ids that had once an entity but now are 
		std::vector<uint64_t> freed_id;


		//the lowest unallocated id that has not interacted with
		uint64_t lowest_unallocatedid = 0;
	};


	

}