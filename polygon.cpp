#include "polygon.h"

Polygon::Polygon(const std::vector<Point>& points) : points_(points) {
	
}

Polygon::~Polygon() {

}

void Polygon::draw(SDL_Renderer* renderer) {
	for(uint8_t i = 0; i < points_.size() - 1; i++) {
		SDL_RenderDrawLine(renderer, points_[i].x_, points_[i].y_,
					     points_[i+1].x_, points_[i+1].y_); 
	}
	SDL_RenderDrawLine(renderer, points_.back().x_, points_.back().y_,
				     points_.front().x_, points_.front().y_); 
}
