#include "../include/triangle_group_ship.h"
#include "../include/player.h"
#include <iostream>

extern PlayerPtr player;

TriangleGroupShips::TriangleGroupShips(EnemyShipPtr leader) : GroupShips(leader, GroupShips::FormationType::SQUARE) {

}

TriangleGroupShips::~TriangleGroupShips() {

}

const Point TriangleGroupShips::get_position_ship(const uint8_t id) const {
    Point leader_pos = leader_->get_position();
    Vector2<float> leader_direction = leader_->get_velocity();
    if(leader_->is_current_state(State::ATTACKING)) {
        leader_direction = player->get_position() - leader_->get_position();
    }

    leader_direction.normalize();

    Vector2<float> leader_direction_t = leader_direction.get_normal();

    Vector2<float> base_group = -leader_direction;
    base_group = base_group*75.f;
	
    float offset_per_stage = 50.f*(id/2 + 1);

    return Point(leader_pos + base_group + leader_direction_t*offset_per_stage
                       - leader_direction*(id/2)*75.f - leader_direction_t*(id%2)*2.f*offset_per_stage);
}

