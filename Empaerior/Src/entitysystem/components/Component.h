#pragma once

#include <string>
#include "../../graphics/rendering/Camera.h"
namespace Empaerior
{

	//Some predifined components, feel free not to use them
	struct Print_Component 
	{
		std::string message = "succes";
	};

	struct Position_Component
	{
		int x = 12;
		int y = 10;
	};

	//camera that follows an entity
	struct Camera_Component
	{
		Empaerior::Camera camera;
	};




}