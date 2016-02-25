#include "ship.h"

Ship::Ship(const Rectangle& box) : Entity(box), life_(100) {

}

Ship::~Ship() {

}

float Ship::compute_force() const {
	return 0.0f;	
}

void Ship::update() {
	move();
}

void Ship::move() {
	box_.translate(Vector2<float>(1.0f, 1.0f));
}
