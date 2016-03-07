#include "entity.h"
#include "math.h"

Entity::Entity(const Rectangle& box) : box_(box), center_mass_(Math::mean(box.get_points())) {

}

Entity::~Entity() {

}

void Entity::draw(SDL_Renderer* renderer) {
    box_.draw(renderer);
}

const Rectangle& Entity::get_box() const {
    return box_;
}

const Point& Entity::get_position() const {
    return center_mass_;
}
