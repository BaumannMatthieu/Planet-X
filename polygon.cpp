#include <cmath>
#include "polygon.h"
#include "matrix22.h"
#include "math.h"

Polygon::Polygon(const std::vector<Point>& points) : Primitive(points, Math::mean(points)) {
	
}

Polygon::~Polygon() {

}

void Polygon::rotate(const float ang) {
	float c = std::cos(ang);
	float s = std::sin(ang);
	Matrix22<float> mat_r(c, s,
			     -s, c);
	for(auto& point : points_) {
		point = Math::rotate(point, pos_, mat_r);
	}
}

void Polygon::scale(const float factor) {
	for(auto& point : points_) {
		point = point*factor;
	}
	pos_ = Math::mean(points_);
}

bool Polygon::is_polygon() const {
	return true;
}
