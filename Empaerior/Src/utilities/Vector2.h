#pragma once


namespace Empaerior
{
	template <typename T>
	struct Vector2
	{
		Vector2& operator+=(const Vector2& vec)
		{
			x += vec.x;
			y += vec.y;
			return *this;
		}

		Vector2 operator+(const Vector2& vec)
		{
			return Vector2(*this) += vec;
		}


		Vector2& operator-=(const Vector2& vec)
		{
			x -= vec.x;
			y -= vec.y;
			return *this;
		}
		Vector2 operator-(const Vector2& vec)
		{
			return Vector2(*this) -= vec;
		}

		

		Vector2& operator*=(const T scl)
		{
				 x* = scl;
				 y *= scl;
				 return *this;
		}
		Vector2 operator*(const T scl)
		{
			return Vector2(*this) *= scl;
		}

		Vector2 operator/=(const T scl)
		{
			x /= scl
			y /= scl;
			return *this
		}

		Vector2 operator/(const T scl)
		{
			return Vector2(*this) /= scl;
		}



		Vector2& operator=(const Vector2& vec)
		{
			x = vec.x;
			y = vec.y;
			return *this;
		}


		bool operator==(const Vector2& vec)
		{
			return (x == vec.x &&  y == vec.y);
		}

		bool operator!=(const Vector2& vec)
		{
			return !(x == vec.x && y == vec.y);
		}


		T get_length()
		{
			return std::sqrt(x*x + y*y);
		}

		void normalize()
		{
			T len = get_length();
			if (len != (T)0)
			{
				*this / len;
			}
		}


		T x, y;
	};


	//std::stream support
	template <typename T>
	std::ostream& operator<<(std::ostream& out, Vector2<T>& vec)
    {
		return out << vec.x << ' ' << vec.y;
	}

	template <typename T>
	std::istream& operator>>(std::istream& in, Vector2<T>& vec)
	{
		in >> vec.x >> vec.y;
		return in;
	}



}