#pragma once

#include <string>

namespace Empaerior
{

	//base componentclass,  all component inherit from it
	class Component
	{
	public:
		virtual ~Component() {  };
		
	};

	
	class Print_Component 
	{
	
	public:
		virtual ~Print_Component() {  };
		std::string message = "succes";
	};





}