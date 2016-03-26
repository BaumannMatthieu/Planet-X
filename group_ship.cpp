#include "group_ship.h"
#include "player.h"
#include "context_scene.h"
#include "scriptable.h"

extern PlayerPtr player;
extern ContextScene scene_;

GroupShips::GroupShips(EnemyShipPtr leader, const FormationType formation) :
	 leader_(leader),
	 formation_(formation) {

}

GroupShips::~GroupShips() {
    
}

void GroupShips::add_ship(EnemyShipPtr ship) {
	std::set<StatePtr> states_follower_ship;
        
	const uint8_t id = ships_.size();

        ship->set_position(get_position_ship(id));

        StatePtr obstacle_avoidance = std::make_shared<State>(State::AVOIDANCE, [ship] (const StatePtr current_state) {
            Vector2<float> ship_velocity = ship->get_velocity();
            float dynamic_length = ship_velocity.get_norme()/ship->get_max_velocity();
            Point ahead = ship->get_position() + (ship_velocity/ship_velocity.get_norme())*dynamic_length*50.f;
            Point ahead_half = ship->get_position() + (ship_velocity/ship_velocity.get_norme())*dynamic_length*25.5f;

            AvoidablePtr obstacle = Avoidable::get_most_threatening_obstacle(ship, ship->get_position(),
            ahead, ahead_half, scene_.get_obstacles());

            if(obstacle != nullptr) {
                Vector2<float> avoidance_force(ahead - obstacle->get_circle().get_pos());
                avoidance_force.normalize();
                avoidance_force = avoidance_force*ship->get_max_avoidance_force();  
            
                ship->add_force(avoidance_force);
            }            
        });

        StatePtr follow_leader = std::make_shared<State>(State::FOLLOW_LEADER, [ship, this, id] (const StatePtr current_state) {
            ship->add_force(ship->compute_arrive_force(ship->get_position(), get_position_ship(id)));
            if(leader_->is_current_state(State::ATTACKING)) {
                ship->insert_state(current_state->get_next_state(State::ATTACKING));
            }
        });
        
        StatePtr attacking = std::make_shared<State>(State::ATTACKING, [ship, this] (const StatePtr current_state) {
                ship->cast_missile(player->get_position() - leader_->get_position());
                if(!leader_->is_current_state(State::ATTACKING)) {
                    ship->erase_state(current_state);
                }
        });

        follow_leader->set_next_state(State::ATTACKING, attacking);

        states_follower_ship.insert(follow_leader);
        states_follower_ship.insert(obstacle_avoidance);

        ship->set_current_states(states_follower_ship);
	ships_.insert(ship);
}

