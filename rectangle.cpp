#include "rectangle.h"

Rectangle::Rectangle(const Point& pos, const float w, const float h) : Primitive({}, pos), w_(w), h_(h) {
	points_.push_back(pos_);
	points_.push_back(pos_ + Point(w_, 0.0f));
	points_.push_back(pos_ + Point(w_, h_));
	points_.push_back(pos_ + Point(0.0f, h_));
}

Rectangle::~Rectangle() {
}

bool Rectangle::is_rectangle() const {
	return true;
}

const Vector2<float> Rectangle::get_size() const {
	return Vector2<float>(w_, h_);
}
