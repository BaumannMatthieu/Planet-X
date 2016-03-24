#include "rectangle.h"
#include "math.h"
#include <iostream>

Rectangle::Rectangle() {

}

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

bool Rectangle::intersection(const Rectangle& r1, const Rectangle& r2) {
       if(r1.pos_.x_ + r1.w_ < r2.pos_.x_ || 
          r1.pos_.y_ + r1.h_ < r2.pos_.y_ || 
          r2.pos_.x_ + r2.w_ < r1.pos_.x_ ||
          r2.pos_.y_ + r2.h_ < r1.pos_.y_) {
            return false;
        }

        return true;
}

bool Rectangle::intersection(const Point& p, const Rectangle& r) {
       if(p.x_ >= r.pos_.x_ && 
          p.x_ <= r.pos_.x_ + r.w_ && 
          p.y_ >= r.pos_.y_ &&
          p.y_ <= r.pos_.y_ + r.h_) {
            return true;
        }

        return false;
}

bool Rectangle::intersection(const Point& p1, const Point& p2, const Rectangle& r) {
    for(unsigned int i = 0; i < r.points_.size() - 1; i++) {
        if(Math::intersect_segment(p1, p2, r.points_[i], r.points_[i + 1])) {
            return true;
        }
    }
    if(Math::intersect_segment(p1, p2, r.points_.back(), r.points_.front())) {
        return true;
    }
    return false; 
}

Rectangle::Rectangle(const Rectangle& rect) {
    *this = rect;
}

Rectangle& Rectangle::operator=(const Rectangle& rect) {
    Primitive::operator=(rect);
    if(this != &rect) {
        w_ = rect.w_;
        h_ = rect.h_;
    }
    return *this;
}
