#include <iostream>
#include "shoot.h"
#include "rectangle.h"

Shoot::Shoot(const std::weak_ptr<Ship> caster, const Point& position, const Point& focus, const float speed, const SDL_Color& color) : Missile(caster, focus, 5, color), vertice_(position), speed_(speed) {
    velocity_ = focus_ - vertice_.center_mass_;
    velocity_.normalize();
    velocity_ = velocity_*speed_;
    length_ = 30.f;
}

Shoot::~Shoot() {

}
        
void Shoot::draw(SDL_Renderer* renderer) {
    Point back_light_point(vertice_.center_mass_ - (velocity_/velocity_.get_norme())*length_);

    SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);
//    Renderable::draw_line(renderer, vertice_.center_mass_, back_light_point);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void Shoot::update() {
    move();
}

void Shoot::move() {
    vertice_.center_mass_ = vertice_.center_mass_ + velocity_;
}

bool Shoot::isShoot() const {
    return true;
}

bool Shoot::compute(const Rectangle& rect) const {
    return Rectangle::intersection(vertice_.center_mass_, rect); 
}

const Point& Shoot::get_position() const {
    return vertice_.center_mass_;
}

bool Shoot::isVertice() const {
    return true;
}
