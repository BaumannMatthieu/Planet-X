#include <iostream>
#include "ship.h"
#include "path.h"
#include "math.h"
#include "shoot.h"

#include "context_scene.h"

extern ContextScene scene_;

Ship::Ship(const Rectangle& box) : Entity(box), life_(100),
rad_focus_(500), rad_attack_(300), rad_near_(100) {
	mass_ = 20;
    max_velocity_ = 10.0f;
    max_force_ = 15; 
	velocity_ = Vector2<float>(-0.1f, -0.1f);
	
    Point seek_pos(512.f, 384.f);   
/*	
    attacking_displacement_.add_point(seek_pos + Point(200.f, 0.f));	    
    attacking_displacement_.add_point(seek_pos + Point(0.f, 200.f));	    
    attacking_displacement_.add_point(seek_pos + Point(-200.f, 0.f));	    
    attacking_displacement_.add_point(seek_pos + Point(0.f, -200.f));	    
*/
    uint8_t n = 10;
    /*
    for(uint8_t i = 0; i < n; i++) {
        attacking_displacement_.add_point(seek_pos + Point(200.f*std::cos(2*3.14f*i/n), 200.f*std::sin(2*3.14f*i/n)));
    }
    */
    for(uint8_t i = 0; i < n; i++) {
        attacking_displacement_.add_point(seek_pos + Point(200.f*std::cos(2*3.14f*i/n), 100.f*std::sin(2*3.14f*i/n)));
    }

	StatePtr wandering = std::make_shared<State>([this] (const StatePtr current_state) {
		/* wandering algorithme */
		Point seek_pos(512.f, 384.f);   
		float distance = Vector2<float>::distance(seek_pos, center_mass_);

		if(distance <= rad_focus_) {
			current_states_.erase(current_state);
			current_states_.insert(current_state->get_next_state(State::ATTACK_DISPLACEMENT));
			current_states_.insert(current_state->get_next_state(State::ATTACKING));
        }
	});

	StatePtr attack_moving = std::make_shared<State>([this] (const StatePtr current_state) {
		Point seek_pos(512.f, 384.f);   
		float distance = Vector2<float>::distance(seek_pos, center_mass_);

        force_ = attacking_displacement_.execute(shared_from_this());
        
		if(distance >= rad_focus_) {
			current_states_.erase(current_state);
			current_states_.insert(current_state->get_next_state(State::WANDERING));
		}
	});
	
    StatePtr attacking = std::make_shared<State>([this] (const StatePtr current_state) {
		Point seek_pos(512.f, 384.f);   

        if(Shoot::is_castable()) {
            ShootPtr shoot_ptr = std::make_shared<Shoot>(center_mass_, seek_pos);  
	        scene_.add_entity(shoot_ptr);
        }
    });


	wandering->set_next_state(State::ATTACK_DISPLACEMENT, attack_moving);
	wandering->set_next_state(State::ATTACKING, attacking);

	attack_moving->set_next_state(State::WANDERING, wandering);

	current_states_.insert(wandering);
}

Ship::~Ship() {
    
}

void Ship::update() {
	execute();
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
