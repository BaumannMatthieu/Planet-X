#include "box.h"
#include "rectangle.h"
#include "math.h"

Box::Box(const Rectangle& rectangle) : rect_(rectangle), center_mass_(Math::mean(rect_.get_points())) {

}

Box::~Box() {

}
        
const Rectangle& Box::get_box_rect() const {
    return rect_;
}

const Point& Box::get_position() const {
    return center_mass_;
}
