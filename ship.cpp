#include <iostream>
#include "ship.h"

Ship::Ship(const Rectangle& box) : Entity(box), life_(100),
rad_focus_(500), rad_attack_(300), rad_near_(100) {
    mass_ = 1000;
    //velocity_ = Vector2<float>((static_cast<float>(std::rand())/RAND_MAX)*2.f - 1.f, (static_cast<float>(std::rand())/RAND_MAX)*2.f - 1.f); 
    velocity_ = Vector2<float>(-0.01f, -0.01f);
    t = true; 
}

Ship::~Ship() {
    
}

const Vector2<float> Ship::compute_seek_force() const {
    Point seek_pos(500.f, 300.f);   
    Vector2<float> desired_velocity = seek_pos - center_mass_;
    desired_velocity.normalize();
    
    return desired_velocity - velocity_;	
}

const Vector2<float> Ship::compute_flee_force() const {
    return -compute_seek_force();	
}

const Vector2<float> Ship::compute_circular_displacement_force() const {
    Point focus_pos(512.f, 384.f);   
    Vector2<float> radial_vector = center_mass_ - focus_pos;
    radial_vector.normalize();
    radial_vector = radial_vector*10.f;
    std::cout << radial_vector.x_ << " " << radial_vector.y_ << std::endl;
    return Vector2<float>(-radial_vector.y_, radial_vector.x_);
}

const Vector2<float> Ship::compute_force() const {
    Vector2<float> force(0.f, 0.f);

    Point seek_pos(512.f, 384.f);   
    float distance = Vector2<float>::distance(seek_pos, center_mass_);
    if(distance <= rad_near_) {
        force = force + compute_flee_force();
    } else if(distance <= rad_attack_ && distance > rad_near_) {
        force = force + compute_circular_displacement_force();
    } else if(distance <= rad_focus_ && distance > rad_attack_) {
        force = force + compute_seek_force();        
    }

    return force;	
}

void Ship::update() {
    Point seek_pos(512.f, 384.f);   
    float distance = Vector2<float>::distance(seek_pos, center_mass_);
    if(distance <= rad_near_) {
        t = true;
    } else if(distance <= rad_attack_ && distance > rad_near_ && t) {
        velocity_ = Vector2<float>(0.f, 0.f);
        t = false;
    } else if(distance <= rad_focus_ && distance > rad_attack_) {
        t = true;
    }

    Vector2<float> force = compute_force();
    acceleration_ = force/mass_;
    
    velocity_ = velocity_ + acceleration_;

	move();
}

void Ship::move() {
    box_.translate(velocity_);
    center_mass_ = center_mass_ + velocity_;
    //box_.translate(Vector2<float>(0.1f, 0.1f));
}
