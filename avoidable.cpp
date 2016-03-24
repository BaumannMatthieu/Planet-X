#include <iostream>
#include "avoidable.h"
#include "math.h"
#include "vector2.h"

Avoidable::Avoidable(const Rectangle& rect) : circle_(Math::mean(rect.get_points()), Math::norme(Vector2<float>(Math::mean(rect.get_points()) - Math::get_farthest_point(Math::mean(rect.get_points()), rect.get_points())))) {
    
}

Avoidable::~Avoidable() {

}

const Circle& Avoidable::get_circle() const {
    return circle_;
}

const AvoidablePtr Avoidable::get_most_threatening_obstacle(const AvoidablePtr& this_entity, const Point& position, const Point& ahead, const Point& ahead2, const std::set<AvoidablePtr>& avoidables) {
    AvoidablePtr most_threatening = nullptr;

    for(auto& avoidable : avoidables) {
        if(this_entity != avoidable) {
            const Circle circle = avoidable->get_circle();
            float radius = circle.get_radius();
            float this_radius = this_entity->get_circle().get_radius();
            Point center = circle.get_pos();

            if(Math::distance(ahead, center) <= radius + this_radius || Math::distance(ahead2, center) <= radius + this_radius||Math::distance(position, center) <= radius + this_radius) {
                if(most_threatening != nullptr) {
                    if(Math::distance(center, position) > Math::distance(most_threatening->get_circle().get_pos(), position)) {
                        most_threatening = avoidable;
                        continue;
                    }
                }

                if(most_threatening == nullptr) {
                    most_threatening = avoidable;
                }
            }
        }
    }

    return most_threatening;
}
   

