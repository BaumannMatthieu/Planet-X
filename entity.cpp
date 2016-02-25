#include "entity.h"

Entity::Entity(const Rectangle& box) : box_(box) {

}

Entity::~Entity() {

}

void Entity::draw(SDL_Renderer* renderer) {
    box_.draw(renderer);
}

const Rectangle& Entity::get_box() const {
    return box_;
}
