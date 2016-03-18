#include <iostream>
#include "blaster_ship.h"
#include "centered_path.h"
#include "math.h"
#include "shoot.h"
#include "missile_handler.h"
#include "player.h"

extern PlayerPtr player;

Blaster::Blaster(const Rectangle& box) : Ship(box), rad_focus_(500) {
	mass_ = 20;
    SDL_Color color_missile = {255, 0, 0, 255};
    missile_handler = std::make_shared<MissileHandler>(color_missile);
    attacking_displacement_ = std::make_shared<CenteredPath>(player->get_position());
    max_velocity_ = 10.0f;
    max_force_ = 15; 
	velocity_ = Vector2<float>(-0.1f, -0.1f);
	
    Point seek_pos(player->get_position());   
    uint8_t n = 10;
    for(uint8_t i = 0; i < n; i++) {
        attacking_displacement_->add_point(seek_pos + Point(100.f*std::cos(2*3.14f*i/n), 200.f*std::sin(2*3.14f*i/n)));
    }
/*	
    attacking_displacement_.add_point(seek_pos + Point(200.f, 0.f));	    
    attacking_displacement_.add_point(seek_pos + Point(0.f, 200.f));	    
    attacking_displacement_.add_point(seek_pos + Point(-200.f, 0.f));	    
    attacking_displacement_.add_point(seek_pos + Point(0.f, -200.f));	    
*/
    /*
    for(uint8_t i = 0; i < n; i++) {
        attacking_displacement_.add_point(seek_pos + Point(200.f*std::cos(2*3.14f*i/n), 200.f*std::sin(2*3.14f*i/n)));
    }
    */

	StatePtr wandering = std::make_shared<State>([this] (const StatePtr current_state) {
		/* wandering algorithme */
        Point seek_pos(player->get_position());   
		float distance = Vector2<float>::distance(seek_pos, center_mass_);

		if(distance <= rad_focus_) {
			current_states_.erase(current_state);
			current_states_.insert(current_state->get_next_state(State::ATTACK_DISPLACEMENT));
			current_states_.insert(current_state->get_next_state(State::ATTACKING));
        }
	});

	StatePtr attack_moving = std::make_shared<State>([this] (const StatePtr current_state) {
        Point seek_pos(player->get_position());   
		float distance = Vector2<float>::distance(seek_pos, center_mass_);
       
        attacking_displacement_->update(seek_pos); 

        force_ = attacking_displacement_->execute(shared_from_this());
        
		if(distance >= rad_focus_) {
			current_states_.erase(current_state);
			current_states_.insert(current_state->get_next_state(State::WANDERING));
		}
	});
	
    StatePtr attacking = std::make_shared<State>([this] (const StatePtr current_state) {
        missile_handler->cast_missile(center_mass_, player->get_position(), 10.0f);
    });


	wandering->set_next_state(State::ATTACK_DISPLACEMENT, attack_moving);
	wandering->set_next_state(State::ATTACKING, attacking);

	attack_moving->set_next_state(State::WANDERING, wandering);

	current_states_.insert(wandering);
}

Blaster::~Blaster() {
    
}
void Blaster::update() {
	execute();
    

    Ship::update();
}

