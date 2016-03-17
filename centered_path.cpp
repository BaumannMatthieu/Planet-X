#include "centered_path.h"

CenteredPath::CenteredPath(const Point& center) : center_(center) {

}

CenteredPath::~CenteredPath() {

}

void CenteredPath::update(const Point& new_center) {
    for(auto& point : points_) {
        point = point + new_center - center_;
    }
    center_ = new_center;
}
