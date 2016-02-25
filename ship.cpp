#include "ship.h"

Ship::Ship(const Rectangle& box) : Entity(box), life_(100),
rad_focus_(500), rad_attack_(400), rad_near_(100) {
    mass_ = 1000;
    velocity_ = Vector2<float>((static_cast<float>(std::rand())/RAND_MAX)*2.f - 1.f, (static_cast<float>(std::rand())/RAND_MAX)*2.f - 1.f); 
}

Ship::~Ship() {

}

const Vector2<float> Ship::compute_seek_force() const {
    Vector2<float> seek_pos(50.f, 50.f);   
    
    return Vector2<float>();	
}

const Vector2<float> Ship::compute_force() const {
      
    return Vector2<float>(0.f, 0.f);	
}

void Ship::update() {
    Vector2<float> force = compute_force();
    acceleration_ = force/mass_;
    velocity_ = velocity_ + acceleration_;

	move();
}

void Ship::move() {
    box_.translate(velocity_);
	//box_.translate(Vector2<float>(0.1f, 0.1f));
}
