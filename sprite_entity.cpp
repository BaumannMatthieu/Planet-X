#include "sprite_entity.h"

SpriteEntity::SpriteEntity(const Rectangle& box) : Box(box), pos_sprite_(box.get_points().front()) {

}

SpriteEntity::~SpriteEntity() {

}

void SpriteEntity::draw(SDL_Renderer* renderer) {
    rect_.draw(renderer);
}
