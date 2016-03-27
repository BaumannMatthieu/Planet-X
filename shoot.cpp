#include <iostream>
#include "shoot.h"
#include "rectangle.h"

Shoot::Shoot(const std::weak_ptr<Ship> caster, const Point& position, const Vector2<float>& direction, const float speed, const SDL_Color& color) : Missile(caster, 20, color),
                                 direction_(direction),
                                 speed_(speed),
                                 length_(30.f),
                                 position_(position), 
                                 end_position_(position) {
    direction_.normalize();
    velocity_ = direction_;

    end_position_.center_mass_ = position_.center_mass_ - velocity_*length_;

    velocity_ = velocity_*speed_;
}

Shoot::~Shoot() {

}
        
void Shoot::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);
    Renderable::draw_line(renderer, position_.center_mass_, end_position_.center_mass_);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void Shoot::update() {
    move();
}

void Shoot::move() {
    position_.center_mass_ = position_.center_mass_ + velocity_;
    end_position_.center_mass_ = end_position_.center_mass_ + velocity_;
}

bool Shoot::compute(const Rectangle& rect) const {
    return Rectangle::intersection(position_.center_mass_, end_position_.center_mass_, rect) ||
           Rectangle::intersection(position_.center_mass_, rect); 
}

const Point& Shoot::get_position() const {
    return position_.center_mass_;
}
/*
const Point& Shoot::get_end_position() const {
    return end_position_.center_mass_;
}
*/
bool Shoot::isVertice() const {
    return true;
}
