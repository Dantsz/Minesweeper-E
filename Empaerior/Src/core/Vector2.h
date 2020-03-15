#pragma once
#include <sstream>
#include "Point2.h"
namespace Empaerior
{
	template <typename T>
	//Vector2 is just a Point2
	using Vector2 = Point2<T>;

}

#pragma region Vector_functions

namespace Empaerior
{
	//These work just fine on Point2
	//But they are Vector functions because they should be used on Vectors
	namespace Vector2_Funct
	{
		template <typename T>
		inline T get_vector2_length(const Empaerior::Vector2<T>& vec)
		{
			return std::sqrt(vec.x * vec. x + vec.y * vec.y);
		}

		template <typename T>
		inline void normalize_vector2(Empaerior::Vector2<T>& vec)
		{
			T len = get_vector2_length(vec);
			if (len != (T)0)
			{
				vec /= len;
			}
		}
	}

}


#pragma endregion

