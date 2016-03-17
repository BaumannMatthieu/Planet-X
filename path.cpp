#include "path.h"
#include "ship.h"
#include "movable.h"

Path::Path(const float radius, const bool repeat) : radius_(radius), repeat_(repeat) {

}

Path::Path(const std::vector<Point>& points, const float radius, const bool repeat)
 : points_(points), radius_(radius), repeat_(repeat) {
    current_destination_ = 0;
}

Path::~Path() {

}

void Path::add_point(const Point& point) {
    if(points_.empty()) {
        current_destination_ = 0;
    }

    points_.push_back(point);
}

void Path::clear() {
    points_.clear();
}

const Vector2<float> Path::execute(std::shared_ptr<Ship> ship) {
    Point pos = ship->get_position();
    if(!repeat_ && current_destination_ == points_.size() - 1) {
        return ship->compute_arrive_force(pos, points_[current_destination_]);
    }

    Vector2<float> distance_vector = points_[current_destination_] - pos;
    float distance = distance_vector.get_norme();
    if(distance <= radius_) {
        if(current_destination_ == points_.size() - 1) {
            if(repeat_) {
                current_destination_ = 0;
            }
        } else {
            current_destination_++;
        }
    }
    
    return ship->compute_seek_force(pos, points_[current_destination_]);
}

