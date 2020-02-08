#pragma once 




namespace Empaerior
{

	//Static rect, without any transformation
	template <typename T>
	struct S_Rect
	{
		T x, y;
		T w, h;
	};
	//normal rect
	template <typename T , typename rotation_type>
	struct T_Rect
	{
		S_Rect<T> dimensions;
		rotation_type angle; // the angle of rotation
	};



	enum Rect_Corners
	{
		top_left = 0,
		bottom_left = 1,
		top_right = 2,
		bottom_right = 3

	};
	namespace Rect_Funct
	{

		//functions to get the corner
		//top_left
		//bottom_left
		//top_right
		//bottom_right

		template <typename T, typename rotation_type>
		std::pair<T, T> get_rect_corner(const T_Rect<T, rotation_type>& rect, const Rect_Corners& corner_flag)
		{
			T o_x = rect.dimensions.x + rect.dimensions.w / 2;
			T o_y = rect.dimensions.y + rect.dimensions.h / 2;

			std::pair<T, T> corner;

			//rotating the point clockwise
			corner.first = o_x + (rect.dimensions.x + bool(corner_flag & 2) * rect.dimensions.w - o_x) * Empaerior::Math::cosd(rect.angle) - (rect.dimensions.y + bool(corner_flag & 1) * rect.dimensions.h - o_y) * Empaerior::Math::sind(rect.angle);
			corner.second = o_y + (rect.dimensions.y + bool(corner_flag & 1) * rect.dimensions.h - o_y) * Empaerior::Math::cosd(rect.angle) + (rect.dimensions.x + bool(corner_flag & 2) * rect.dimensions.w - o_x) * Empaerior::Math::sind(rect.angle);

			return corner;
		}

		template <typename T, typename rotation_type>
		T get_rect_area(const T_Rect<T, rotation_type>& rect)
		{
			return rect.dimensions.w * rect.dimensions.h;
		}


	}




}


