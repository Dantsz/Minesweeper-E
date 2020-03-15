#pragma once

namespace Empaerior
{
#pragma region Point
	//A point
	template<typename T>
	struct Point2
	{
		T x, y;

#pragma region operators
		Point2& operator+=(const Point2& point)
		{
			x += point.x;
			y += point.y;
			return *this;
		}

		Point2 operator+(const Point2& point)
		{
			return Vector2(*this) += point;
		}



		Point2& operator-=(const Point2& point)
		{
			x -= point.x;
			y -= point.y;
			return *this;
		}
		Point2 operator-(const Point2& point)
		{
			return Point2(*this) -= point;
		}



		Point2& operator*=(const T scl)
		{
			x* = scl;
			y *= scl;
			return *this;
		}
		Point2 operator*(const T scl)
		{
			return Point2(*this) *= scl;
		}

		Point2 operator/=(const T scl)
		{
			x /= scl;
			y /= scl;
			return *this;
		}

		Point2 operator/(const T scl)
		{
			return Point2(*this) /= scl;
		}



		Point2& operator=(const Point2& point)
		{
			x = point.x;
			y = point.y;
			return *this;
		}

		bool operator==(const Point2& point)
		{
			return (x == point.x && y == point.y);
		}

		bool operator!=(const Point2& point)
		{
			return !(x == point.x && y == point.y);
		}

#pragma endregion
	};


}
//std::stream compatibility
template <typename T>
std::ostream& operator<<(std::ostream& out, Empaerior::Point2<T>& point)
{
	return out << point.x << ' ' << point.y;
}

template <typename T>
std::istream& operator>>(std::istream& in, Empaerior::Point2<T>& point)
{
	in >> point.x >> point.y;
	return in;
}