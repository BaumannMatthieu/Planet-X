#ifndef __MATH_H__
#define __MATH_H__

#include <vector>
#include <cmath>
#include "vector2.h"
#include "matrix22.h"

namespace Math {
	inline const Vector2<float> mean(const std::vector<Vector2<float>>& vectors) {
		Vector2<float> result(0.f, 0.f);
		for(auto& vector : vectors) {
			result = result + vector;
		}
		return (result/vectors.size());
	}

	inline const Vector2<float> rotate(const Vector2<float>& vector,
				     const Vector2<float>& center,
				     const Matrix22<float>& matrix) {
		return matrix*(vector - center) + center;
	}

    inline void truncate(Vector2<float>& vector, float max_norme) {
        float norme_vector = vector.get_norme();
        if(norme_vector < max_norme) {
            return;
        }
        vector = vector*(max_norme/norme_vector);
    }
};

#endif
