#include "../include/primitive.h"
#include "../include/math.h"

Primitive::Primitive() {

}

Primitive::Primitive(const std::vector<Point>& points, const Point& pos) : points_(points), pos_(pos) {

}

Primitive::~Primitive() {

}

void Primitive::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for(uint8_t i = 0; i < points_.size() - 1; i++) {
		draw_line(renderer, points_[i], points_[i + 1]);
	}
	draw_line(renderer, points_.back(), points_.front());
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void Primitive::translate(const Vector2<float>& vector) {
	for(auto& point : points_) {
		point = point + vector;
	}
    pos_ = pos_ + vector;    
}

void Primitive::update() {

}

bool Primitive::is_rectangle() const {
	return false;
}

bool Primitive::is_polygon() const {
	return false;
}

const Point& Primitive::get_pos() const {
    return pos_;
}

const std::vector<Point>& Primitive::get_points() const {
    return points_;
}

Primitive& Primitive::operator=(const Primitive& primitive) {
    if(this != &primitive) {
        points_ = primitive.points_;
        pos_ = primitive.pos_;
    }
    
    return *this;
}
