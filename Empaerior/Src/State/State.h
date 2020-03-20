#pragma once


#include "rendering/objects/Sprite.h"
#include "rendering/Camera.h"

//entity tests

#include "core/ecs/ECS.h"
#include "systems/systems.h"


#include "core/defines/Defines.h"
/*
	A state of the engine, which updates the layers contained in it's layers stack
*/

namespace Empaerior {
	class  State
	{
	public:
		State();
		virtual ~State() {

		};

		virtual void Update(const Empaerior::u_int dt) = 0;
		virtual void Render() = 0 ;//renders the state
		virtual void handleevents(Empaerior::Event& event) = 0;

		void set_camera(const Empaerior::Int_Rect& rect);//sets the camera to the specified sdl rect
		
		Empaerior::Camera& get_camera() { return camera; } // return the camera



		Empaerior::ECS ecs;
	protected:


		Empaerior::Camera camera;
		


	
	};
}