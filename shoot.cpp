#include "shoot.h"

Shoot::Shoot(const Point& position, const Point& focus) : Missile(focus, 500, 5, {255, 0, 0, 255}), Vertice(position) {
    velocity_ = focus_ - center_mass_;
    velocity_.normalize();
}

Shoot::~Shoot() {

}
        
void Shoot::draw(SDL_Renderer* renderer) {
    Point back_light_point(center_mass_ - velocity_*10);

    SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);
    Renderable::draw_line(renderer, center_mass_, back_light_point);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void Shoot::update() {
    move();
}

void Shoot::move() {
    center_mass_ = center_mass_ + velocity_;
}
