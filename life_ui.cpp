#include "life_ui.h"

LifeUi::LifeUi(const ShipPtr ship) : length_max_(60.f), length_(length_max_), offset_(Vector2<float>(length_/2.f, 40.f)), ship_(ship), rect_(ship->get_position() - offset_, length_, 5) {
    
}

LifeUi::~LifeUi() {

}

void LifeUi::draw(SDL_Renderer* renderer) {
    if(length_ == 0.f) {
        return;
    }

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
    rect_.draw(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void LifeUi::update() {
    //rect_.translate(ship_->get_position() - offset_ - rect_.get_pos());

    int16_t life_ship = ship_->get_life();
    length_ = (life_ship/100.f)*length_max_;
    
    rect_ = Rectangle(ship_->get_position() - offset_, length_, 10);
}


