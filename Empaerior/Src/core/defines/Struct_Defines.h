#pragma once
#include <SDL.h>
#include <string>
#include "core/Vector2.h"
#include "core/Rect.h"
#include "core/unsafe_vector.h"
namespace Empaerior
{

	using Int_Rect = SDL_Rect;

	using Float_Rect_S = Empaerior::S_Rect<Empaerior::fl_point>;

	using Float_Rect = Empaerior::T_Rect<Empaerior::fl_point, Empaerior::fl_point>;

	using Vector2f = Vector2<fl_point>;

	using Point2f = Point2<Empaerior::fl_point>;

	using Color = SDL_Color;
}
