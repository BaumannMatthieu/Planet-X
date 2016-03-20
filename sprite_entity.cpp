#include "sprite_entity.h"
#include "rectangle.h"

SpriteEntity::SpriteEntity(const Rectangle& box) : box_(box), pos_sprite_(box.get_points().front()) {

}

SpriteEntity::~SpriteEntity() {

}

void SpriteEntity::draw(SDL_Renderer* renderer) {
    box_.rect_.draw(renderer);
}

bool SpriteEntity::compute(const Rectangle& rect) const {
    return Rectangle::intersection(box_.get_box_rect(), rect);
}

const Point& SpriteEntity::get_position() const {
    return box_.center_mass_;
}

const Rectangle& SpriteEntity::get_box() const {
    return box_.rect_;
}

bool SpriteEntity::isBox() const {
    return true;
}
