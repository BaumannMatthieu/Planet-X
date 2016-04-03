#include "../include/enemy_ship.h"

EnemyShip::EnemyShip(const Rectangle& box) : Ship(box) {

}

void EnemyShip::init_missile_handler() {
    SDL_Color color_missile = {255, 0, 0, 255};
    std::weak_ptr<Ship> weak_from_this(shared_from_this());
    missile_handler = std::make_shared<MissileHandler>(weak_from_this, color_missile);
}

EnemyShip::~EnemyShip() {
    
}
void EnemyShip::update() {
	execute();

    Ship::update();
}

const float EnemyShip::get_max_avoidance_force() const {
    return max_avoidance_force_;
}
