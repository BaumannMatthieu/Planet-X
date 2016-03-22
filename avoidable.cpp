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

const AvoidablePtr Avoidable::get_most_threatening_obstacle(const std::set<AvoidablePtr>& avoidables) {
/*    for(auto& avoidable : avoidables) {
         
    }
*/
    return nullptr;
}
   

