#include <iostream>
#include "shoot.h"
#include "rectangle.h"

Shoot::Shoot(const std::weak_ptr<Ship> caster, const Point& position, const Point& focus, const float speed, const SDL_Color& color) : Missile(caster, focus, 5, color),
                                 speed_(speed),
                                 length_(30.f),
                                 front_(position), 
                                 back_(position) {
    velocity_ = focus_ - front_.center_mass_;
    velocity_.normalize();

    back_.center_mass_ = front_.center_mass_ - velocity_*length_;

    velocity_ = velocity_*speed_;
}

Shoot::~Shoot() {

}
        
void Shoot::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);
    Renderable::draw_line(renderer, front_.center_mass_, back_.center_mass_);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void Shoot::update() {
    move();
}

void Shoot::move() {
    front_.center_mass_ = front_.center_mass_ + velocity_;
    back_.center_mass_ = back_.center_mass_ + velocity_;
}

bool Shoot::isShoot() const {
    return true;
}

bool Shoot::compute(const Rectangle& rect) const {
    return Rectangle::intersection(front_.center_mass_, back_.center_mass_, rect) ||
           Rectangle::intersection(front_.center_mass_, rect); 
}

const Point& Shoot::get_position() const {
    return front_.center_mass_;
}

const Point& Shoot::get_back_position() const {
    return back_.center_mass_;
}

bool Shoot::isVertice() const {
    return true;
}
