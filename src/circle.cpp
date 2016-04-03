#include "../include/circle.h"

Circle::Circle(const Point& point, const float radius) : Primitive() {
    radius_ = radius;
    pos_ = point;
    unsigned int nb_points = 20;
    for(unsigned int i = 0; i < nb_points; i++) {
        points_.push_back(Point(pos_.x_ + radius_*std::cos(i*2*3.14/nb_points), pos_.y_ + radius_*std::sin(i*2*3.14/nb_points)));
    }
}

Circle::~Circle() {

}
        
const float Circle::get_radius() const {
    return radius_;
}
 
