#include <iostream>
#include "ship.h"
#include "path.h"
#include "math.h"
#include "shoot.h"

#include "context_scene.h"

extern ContextScene scene_;

Ship::Ship(const Rectangle& box) : Entity(box), life_(100) {
	mass_ = 20;
    max_velocity_ = 10.0f;
    max_force_ = 15; 
	velocity_ = Vector2<float>(-0.1f, -0.1f);
}

Ship::~Ship() {
    
}

void Ship::update() {
    Math::truncate(force_, max_force_);
	
	acceleration_ = force_/mass_;
    velocity_ = velocity_ + acceleration_;
    Math::truncate(velocity_, max_velocity_);
	move();
}

void Ship::move() {
    rect_.translate(velocity_);
    center_mass_ = center_mass_ + velocity_;
}

bool Ship::is_player() const {
    return false;
}
