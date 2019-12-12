#pragma once
#include "Component.h"
#include <vector>
#include <iostream>
#include <map>
//class that handles/update/render a certain type of component
namespace Empaerior
{


	template <typename  T>
	class ComponentSystem
	{
	public:
		//update a specific component
		void update(T* component) { }


	private:
		std::map<uint64_t, T*> components;
		


	};
	
	//specialization for certain components


}