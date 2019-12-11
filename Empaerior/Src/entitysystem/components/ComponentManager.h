#pragma once
#include "Component.h"
#include <vector>
#include <iostream>
//class that handles/update/render a certain type of component
namespace Empaerior
{


	template <typename  T>
	class ComponentManager
	{
	public:
		//update a specific component
		void update(T* component) { }


	private:
		std::vector<T> components;



	};

	//specialization for certain components
	template <>
	void ComponentManager<Empaerior::Print_Component>::update(Empaerior::Print_Component* component)
	{
		std::cout << component->message << '\n';
	}


}