#include "circle.h"

Circle::Circle(const Point& point, const float radius) : center_mass_(point), radius_(radius) {
    
}

Circle::~Circle() {

}
        
const Point& Circle::get_position() const {
    return center_mass_;
}

const float Circle::get_radius() const {
    return radius_;
}
 
