#include "square_group_ship.h"
#include "player.h"
#include <iostream>

extern PlayerPtr player;

SquareGroupShips::SquareGroupShips(EnemyShipPtr leader) : GroupShips(leader, GroupShips::FormationType::SQUARE) {

}

SquareGroupShips::~SquareGroupShips() {

}

const Point SquareGroupShips::get_position_ship(const uint8_t id) const {
    Point leader_pos = leader_->get_position();
    Vector2<float> leader_direction = leader_->get_velocity();
    if(leader_->is_current_state(State::ATTACKING)) {
        leader_direction = player->get_position() - leader_->get_position();
    }

    leader_direction.normalize();

    Vector2<float> leader_direction_t = leader_direction.get_normal();

    Vector2<float> base_group = -leader_direction;
    base_group = base_group*50.f;

    return Point(leader_pos + base_group + leader_direction_t*50.f
                       - leader_direction*(id/2)*75.f - leader_direction_t*(id%2)*100.f);
}

