#include "player.h"
#include "event_handler.h"
extern EventHandler event_handler; 

Player::Player(const Rectangle& box) : Ship(box) {

}

Player::~Player() {

}

void Player::update() {
    Ship::update();
}

void Player::register_events() {

}

