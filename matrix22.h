#ifndef __MATRIX22_H__
#define __MATRIX22_H__

#include "vector2.h"

template<typename T>
class Matrix22 {
	public:
		Matrix22() { };
		//Matrix22<float>() : a_(1.f), c_(1.f), b_(0.f), d_(0.f) { }
		Matrix22(const T& a, const T& b,
			 const T& c, const T& d)
		: a_(a), b_(b), c_(c), d_(d) {
			
		}

		~Matrix22() { };
	
		inline const Vector2<T> operator*(const Vector2<T>& vector) const {
			return Vector2<T>(a_*vector.x_ + b_*vector.y_,
					  c_*vector.x_ + d_*vector.y_);	
		}

		inline const Matrix22<T> operator*(const Matrix22<T>& mat) const {
			return Matrix22<T>(a_*mat.a_ + b_*mat.c_,
					   a_*mat.b_ + b_*mat.d_,
					   c_*mat.a_ + d_*mat.c_,
					   c_*mat.b_ + d_*mat.d_);	
		}

		inline const Matrix22<T> operator*(const T& lambda)  const {
			return Matrix22<T>(a_*lambda, b_*lambda,
				   	   c_*lambda, d_*lambda);
		}

	private:
		T a_, b_;
		T c_, d_;
};

#endif
