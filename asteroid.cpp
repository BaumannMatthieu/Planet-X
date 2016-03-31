#include "asteroid.h"
#include "math.h"
#include "rectangle.h"
#include <iostream>

Asteroid::Asteroid() : SpriteEntity(Rectangle(Vector2<float>(std::rand()%WINDOW_WIDTH, std::rand()%WINDOW_HEIGHT), 40.f, 40.f)) {
	mass_ = 7;
    max_velocity_ = 1.0f;
    min_velocity_ = 0.1f;
    max_force_ = 5.0; 

/*
    mass_ = 100;
    max_velocity_ = 3.0f;
    min_velocity_ = 0.1f;
    max_force_ = 10;*/
    velocity_ = Vector2<float>(2*(std::rand()/float(RAND_MAX)) - 1.f, 2*(std::rand()/float(RAND_MAX)) - 1.f);
    std::cout << velocity_.x_ << " " << velocity_.y_ << std::endl;
}

Asteroid::~Asteroid() {
    
}

bool Asteroid::is_asteroid() const {
    return true;
}

void Asteroid::update() {
    Math::truncate(force_, max_force_);
	
	acceleration_ = force_/mass_;
    velocity_ = velocity_ + acceleration_;
    if(velocity_.get_norme() >= min_velocity_) {
        Math::truncate(velocity_, max_velocity_);
	    move();
    }

    force_ = Vector2<float>(0.f, 0.f);
}

void Asteroid::move() {
    box_.rect_.translate(velocity_);
    box_.center_mass_ = box_.center_mass_ + velocity_;

    circle_.translate(velocity_);  
}
