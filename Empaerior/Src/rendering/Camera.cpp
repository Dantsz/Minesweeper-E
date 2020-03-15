#include "pch.h"
#include "Camera.h"


namespace Empaerior
{
	void Camera::set_dimensions(const Empaerior::s_int& w, const  Empaerior::s_int& h)
	{

		rect.w = w;
		rect.h = h;
		
	}
}
