#include "path.h"
#include "movable.h"


Path::Path(const float radius, const bool repeat) : radius_(radius), repeat_(repeat) {

}

Path::Path(const std::vector<Point>& points, const float radius, const bool repeat) : points_(points), radius_(radius), repeat_(repeat) {
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

const Vector2<float> Path::execute(std::shared_ptr<Movable> movable) {
    Point pos = movable->get_position();
    if(!repeat_ && current_destination_ >= points_.size()) {
        return movable->compute_arrive_force(pos, points_[current_destination_]);
    }

    Vector2<float> distance_vector = current_destination_ - pos;
    float distance = distance_vector.get_norme();
    if(distance <= radius_) {
        current_destination_++;
        if(repeat_ && current_destination_ >= points_.size()) {
            current_destination_ = 0;
        }
    }

    return movable->compute_seek_force(pos, points_[current_destination_]);
}

