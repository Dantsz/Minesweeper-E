#pragma once

#include <vector>
#include <queue>
#include <unordered_map>
#include <iostream>

#include "../../exceptions/Exceptions.h"
#include "../Entity.h"
#include "Component.h"

namespace Empaerior
{
	//virtual cointainer for polymorphism
	class VCointainer
	{
	public:
		virtual ~VCointainer() {};
		virtual void EntityDestroyed(Entity entity) {};
	};


	//contains..components
	template <typename  T>
	class ComponentCointainer : public VCointainer
	{
	public:
		virtual ~ComponentCointainer() {};

		//update a specific component
		void add_component(Entity& entity,T component)
		{
			try {
				//if the entity does have this type of component throw exception
				if (componenttoentity.find(entity.id) != componenttoentity.end())
				{
					throw E_runtime_exception("Cannot add component: the entity already has this type of component",__FILE__,__LINE__);
				}



				//if there isn't any free space,create one
				if (free_index.empty())
				{
					components.push_back(component);
					entitytocomponent[entity.id] = components.size() - 1;
					componenttoentity[components.size() - 1] = entity.id;

				}
				else//just take an unused component
				{
					components[free_index.front()] = component;
					entitytocomponent[entity.id] = free_index.front();
					componenttoentity[free_index.front()] = entity.id;
					free_index.pop();


				}
			}
			catch(E_runtime_exception & e)
			{
				std::cout << e.what() << '\n';
			}




		}
		void remove_component(Entity& entity)
		{
			try
			{
				//if the entity doesn't have this type of component throw exception
				if (componenttoentity.find(entity.id) == entitytocomponent.end())
				{
					E_runtime_exception("Cannot delete component: the entity doesn't have this type of component", __FILE__, __LINE__);
				}
				
				//get the index of the removed entity
				uint64_t removed_index = entitytocomponent[entity.id];


				//add the id to the list of unused ids
				free_index.push(removed_index);



				//delete the entity from the registries

			
			

			}
			catch (E_runtime_exception & e)
			{
				std::cout << e.what() << '\n';
			}


		}




	private:
		//components vector
		std::vector<T> components;

		//the next component's index to be used
		std::queue<uint64_t> free_index;


		//lookup the component of a entity
		std::unordered_map<uint64_t, uint64_t> entitytocomponent;
		//lookup the entity of a component
		std::unordered_map<uint64_t, uint64_t> componenttoentity;





	};
	
	


}