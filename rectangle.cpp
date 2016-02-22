#include "rectangle.h"

Rectangle::Rectangle(const Vector2<float>& pos, const float w, const float h) : pos_(pos), w_(w), h_(h) {
	points_.push_back(pos_);
	points_.push_back(pos_ + Point(w_, 0.0f));
	points_.push_back(pos_ + Point(w_, h_));
	points_.push_back(pos_ + Point(0.0f, h_));
}

Rectangle::~Rectangle() {
}
