#include "entity.h"

Entity::Entity(const Rectangle& box) : box_(box) {

}

Entity::~Entity() {

}

void Entity::draw(SDL_Renderer* renderer) {
    box_.draw(renderer);
}

void Entity::move() {
    box_.translate(Vector2<float>(1.0f, 1.0f));
}

const Rectangle& Entity::get_box() const {
    return box_;
}
