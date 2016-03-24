#include "group_ship.h"
#include "player.h"
#include "context_scene.h"
#include "scriptable.h"

extern PlayerPtr player;
extern ContextScene scene_;

GroupShips::GroupShips(EnemyShipPtr leader) : leader_(leader) {

}

const Point GroupShips::get_square_formation(const uint8_t id) const {
    Point leader_pos = leader_->get_position();
    Vector2<float> leader_velocity = leader_->get_velocity();
    leader_velocity.normalize();

    Vector2<float> leader_velocity_t = leader_velocity.get_normal();

    Vector2<float> base_group = -leader_velocity;
    base_group = base_group*50.f;

    return Point(leader_pos + base_group + leader_velocity_t*50.f
                       - leader_velocity*(id/2)*75.f - leader_velocity_t*(id%2)*100.f);

}

GroupShips::GroupShips(const std::set<EnemyShipPtr> ships, const EnemyShipPtr leader) : ships_(ships), leader_(leader) {
    unsigned int i = 0; 
    for(auto& ship : ships_) {
        std::set<StatePtr> states_follower_ship;

        ship->set_position(get_square_formation(i));

        StatePtr obstacle_avoidance = std::make_shared<State>([ship] (const StatePtr current_state) {
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

        StatePtr follow_leader = std::make_shared<State>([ship, this, i] (const StatePtr current_state) {
            ship->add_force(ship->compute_arrive_force(ship->get_position(), get_square_formation(i)));
        });
       /* 
        StatePtr attacking = std::make_shared<State>([ship] (const StatePtr current_state) {
            missile_handler->cast_missile(ship->get_position(), player->get_position(), 10.0f);
        });
*/
        states_follower_ship.insert(follow_leader);
        //states_follower_ship.insert(attacking);
        states_follower_ship.insert(obstacle_avoidance);

        ship->set_current_states(states_follower_ship);
        i++;
    }
}

GroupShips::~GroupShips() {
    
}

void GroupShips::add_ship(EnemyShipPtr ship) {
    ships_.insert(ship);
}

