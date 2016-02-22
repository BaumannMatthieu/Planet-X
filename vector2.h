#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include <cmath>

template<typename T>
class Vector2 {
	public:
		Vector2<T>() { }
		Vector2<T>(const T& x, const T& y) : x_(x), y_(y) {
		
		}

		Vector2<T>(const Vector2<T>& vector) {
			x_ = vector.x_;
			y_ = vector.y_;
		}

		~Vector2<T>() {

		}
		
		inline bool operator==(const Vector2<T>& vector) const {
			return (x_ == vector.x_ && y_ == vector.y_);
		}

		inline const Vector2<T> operator+(const Vector2<T>& vector) const {
			return Vector2<T>(x_ + vector.x_, y_ + vector.y_);
		}
		
		inline const Vector2<T> operator-(const Vector2<T>& vector) const {
			return Vector2<T>(x_ - vector.x_, y_ - vector.y_);
		}

		inline const Vector2<T> operator*(const T& lambda) const {
			return Vector2<T>(x_*lambda, y_*lambda);
		}

		inline const T& operator*(const Vector2<T>& vector) const {
			return x_*vector.x_ + y_*vector.y_;
		}
		
		inline const Vector2<T> operator/(const T& lambda) const {
			return Vector2<T>(x_/lambda, y_/lambda);
		}

		void normalize() {
			T norme = std::sqrt(x_*x_ + y_*y_);
	
			*this = *this/norme;
		}

	public:
		T x_;
		T y_;
};

#endif
