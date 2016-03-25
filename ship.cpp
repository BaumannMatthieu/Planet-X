#include <iostream>
#include "ship.h"
#include "path.h"
#include "math.h"
#include "shoot.h"

#include "context_scene.h"

extern ContextScene scene_;

Ship::Ship(const Rectangle& box) : SpriteEntity(box), life_(100) {
	mass_ = 7;
    max_velocity_ = 10.0f;
    min_velocity_ = 1.0f;
    max_force_ = 15; 
	velocity_ = Vector2<float>(-0.1f, -0.1f);
}

Ship::~Ship() {
    
}

void Ship::update() {
    if(isDead()) {
        scene_.delete_entity(shared_from_this());
    }

    Math::truncate(force_, max_force_);
	
	acceleration_ = force_/mass_;
    velocity_ = velocity_ + acceleration_;
    if(velocity_.get_norme() >= min_velocity_) {
        Math::truncate(velocity_, max_velocity_);
	    move();
    }

    force_ = Vector2<float>(0.f, 0.f);
}

void Ship::take_damage(const uint8_t damage) {
    life_ -= damage; 
}

void Ship::move() {
    box_.rect_.translate(velocity_);
    box_.center_mass_ = box_.center_mass_ + velocity_;

    circle_.translate(velocity_);  
}

bool Ship::is_player() const {
    return false;
}

bool Ship::isShip() const {
    return true;
}

bool Ship::isDead() const {
    return (life_ <= 0);
}

const int16_t Ship::get_life() const {
    return life_;
}
