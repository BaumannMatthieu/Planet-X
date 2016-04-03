#include "../include/box.h"
#include "../include/rectangle.h"
#include "../include/math.h"

Box::Box(const Rectangle& rectangle) : rect_(rectangle), center_mass_(Math::mean(rect_.get_points())) {

}

Box::~Box() {

}
        
const Rectangle& Box::get_box_rect() const {
    return rect_;
}

void Box::set_position(const Point& center_mass) {
    rect_.translate(center_mass - center_mass_); 
    center_mass_ = center_mass;
}

const Point& Box::get_position() const {
    return center_mass_;
}
