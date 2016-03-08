#include "entity.h"

Entity::Entity(const Rectangle& box) : Box(box), pos_sprite_(box.get_points().front()) {

}

Entity::~Entity() {

}

void Entity::draw(SDL_Renderer* renderer) {
    rect_.draw(renderer);
}
