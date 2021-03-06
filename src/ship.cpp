#include <iostream>
#include "../include/ship.h"
#include "../include/path.h"
#include "../include/math.h"
#include "../include/shoot.h"

#include "../include/context_scene.h"

extern ContextScene scene;

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
        scene.delete_entity(shared_from_this());
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

void Ship::take_damage(const MissilePtr missile) {
    if(missile->is_laser()) {
        if(!missile_handler->laser_damage_time()) { 
            return;
        }
    }

    life_ -= missile->get_damage(); 

    if(!missile->is_laser()) {
        scene.delete_entity(missile);
    }
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
