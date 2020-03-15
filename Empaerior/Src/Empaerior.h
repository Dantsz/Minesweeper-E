#pragma once


#include "Application.h"
#include "State/State.h"


#include <SDL.h>

#include <SDL_mixer.h>
#include <SDL_ttf.h> 


#include "core/Point2.h"
#include "core/Vector2.h"
#include "core/Rect.h"

#include "assetmanager/AssetManager.h"


#include "rendering/glyphs/Glyphs.h"
#include "rendering/SDLwrappers/Ptr_Wrappers.h"
#include "rendering/SDLwrappers/SDL_Wrappers.h"

#include "core/ecs/ECS.h"
#include "systems/Systems.h"
#include "systems/Component.h"

#include "rendering/Window.h"
#include "rendering/Camera.h"
#include "rendering/objects/Sprite.h"

#include "eventhandler/EventHandler.h"



#ifdef EMP_USE_LOGS

#include "core/debugging/Log.h"
#include "core/debugging/get_data_info.h"
	
#endif