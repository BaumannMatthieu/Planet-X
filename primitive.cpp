#include "primitive.h"
#include "math.h"

Primitive::Primitive() {

}

Primitive::Primitive(const std::vector<Point>& points) : points_(points) {

}

Primitive::~Primitive() {

}

void Primitive::draw(SDL_Renderer* renderer) {
	for(uint8_t i = 0; i < points_.size() - 1; i++) {
		draw_line(renderer, points_[i], points_[i + 1]);
	}
	draw_line(renderer, points_.back(), points_.front());
}

void Primitive::translate(const Vector2<float>& vector) {
	for(auto& point : points_) {
		point = point + vector;
	}
}
