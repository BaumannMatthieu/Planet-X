#include "renderable.h"


Renderable::Renderable() {

}

Renderable::~Renderable() {

}

void Renderable::draw_line(SDL_Renderer* renderer, const Vector2<float>& first_point, const Vector2<float>& second_point) {	
	SDL_RenderDrawLine(renderer, first_point.x_, first_point.y_,
			second_point.x_, second_point.y_);
}
