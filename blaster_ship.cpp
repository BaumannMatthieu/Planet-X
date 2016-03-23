#include <iostream>
#include "blaster_ship.h"
#include "centered_path.h"
#include "math.h"
#include "shoot.h"
#include "missile_handler.h"
#include "player.h"
#include "context_scene.h"

extern PlayerPtr player;
extern ContextScene scene_;

Blaster::Blaster(const Rectangle& box) : Ship(box), rad_focus_(800) {
	mass_ = 20;
    damage_ = 5;
    attacking_displacement_ = std::make_shared<CenteredPath>(player->get_position());
    max_velocity_ = 10.0f;
    max_force_ = 15.f; 
    max_avoidance_force_ = 25.f;
	velocity_ = Vector2<float>(-0.1f, -0.1f);
	
    Point seek_pos(player->get_position());   
    uint8_t n = 10;
    for(uint8_t i = 0; i < n; i++) {
        attacking_displacement_->add_point(seek_pos + Point(300.f*std::cos(2*3.14f*i/n), 300.f*std::sin(2*3.14f*i/n)));
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
		float distance = Vector2<float>::distance(seek_pos, box_.center_mass_);

		if(distance <= rad_focus_) {
			current_states_.erase(current_state);
			current_states_.insert(current_state->get_next_state(State::ATTACK_DISPLACEMENT));
			current_states_.insert(current_state->get_next_state(State::ATTACKING));
        }
	});

	StatePtr obstacle_avoidance = std::make_shared<State>([this] (const StatePtr current_state) {
        float dynamic_length = velocity_.get_norme()/max_velocity_;
        Point ahead = box_.center_mass_ + (velocity_/velocity_.get_norme())*dynamic_length*50.f;
        Point ahead_half = box_.center_mass_ + (velocity_/velocity_.get_norme())*dynamic_length*25.5f;

        AvoidablePtr obstacle = Avoidable::get_most_threatening_obstacle(shared_from_this(), box_.center_mass_,
        ahead, ahead_half, scene_.get_obstacles());

        if(obstacle != nullptr) {
            Vector2<float> avoidance_force(ahead - obstacle->get_circle().get_pos());
            avoidance_force.normalize();
            avoidance_force = avoidance_force*max_avoidance_force_;  
        
            force_ = force_ + avoidance_force;
        }            
    });


	StatePtr attack_moving = std::make_shared<State>([this] (const StatePtr current_state) {
        Vector2<float> vect_player_to_ship(box_.center_mass_ - player->get_position());
        vect_player_to_ship.normalize();

        Point seek_pos(player->get_position() + vect_player_to_ship*rad_focus_*0.5f);
		float distance = Vector2<float>::distance(seek_pos, box_.center_mass_);
         
        //attacking_displacement_->update(seek_pos); 
        force_ = force_ + Movable::compute_arrive_force(box_.center_mass_, seek_pos);
        //attacking_displacement_->execute(shared_from_this());
        
		if(distance >= rad_focus_) {
			current_states_.erase(current_state);
			current_states_.insert(current_state->get_next_state(State::WANDERING));
		}
	});
	
    StatePtr attacking = std::make_shared<State>([this] (const StatePtr current_state) {
        missile_handler->cast_missile(box_.center_mass_, player->get_position(), 10.0f);
    });


	wandering->set_next_state(State::ATTACK_DISPLACEMENT, attack_moving);
	wandering->set_next_state(State::ATTACKING, attacking);

	attack_moving->set_next_state(State::WANDERING, wandering);

	current_states_.insert(wandering);
	current_states_.insert(obstacle_avoidance);
}

void Blaster::init_missile_handler() {
    SDL_Color color_missile = {255, 0, 0, 255};
    std::weak_ptr<Ship> weak_from_this(shared_from_this());
    missile_handler = std::make_shared<MissileHandler>(weak_from_this, color_missile);
}

Blaster::~Blaster() {
    
}
void Blaster::update() {
	execute();

    Ship::update();
}

