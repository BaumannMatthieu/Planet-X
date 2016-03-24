#include "vector2.h"
#include "movable.h"
#include <iostream>

const Vector2<float> Movable::compute_seek_force(const Point& source, const Point& destination) const {
    Vector2<float> desired_velocity = destination - source;
	desired_velocity.normalize();
	desired_velocity = desired_velocity*max_velocity_;
	
    Vector2<float> seek_force = desired_velocity - velocity_;
    
	return seek_force;
}
    
const Vector2<float> Movable::compute_arrive_force(const Point& source, const Point& destination) const {
    Vector2<float> desired_velocity = destination - source;
	float distance = desired_velocity.get_norme();
    desired_velocity.normalize();
    float radius_stop = 100.0f;

    if(distance >= radius_stop) {
        desired_velocity = desired_velocity*max_velocity_;
    } else {
        desired_velocity = desired_velocity*max_velocity_*(distance/radius_stop);
    }
        
	return desired_velocity - velocity_;	
}

const Vector2<float> Movable::compute_flee_force(const Point& source, const Point& destination) const {
	return -compute_seek_force(source, destination);	
}

const Vector2<float> Movable::compute_circular_displacement_force(const Point& source, const Point& destination) const {
	Vector2<float> radial_vector = source - destination;

   	return Vector2<float>(-radial_vector.y_, radial_vector.x_);
}

const Vector2<float>& Movable::get_velocity() const {
    return velocity_;
}

const float Movable::get_max_velocity() const {
    return max_velocity_;
}


void Movable::add_force(const Vector2<float>& delta_force) {
    force_ = force_ + delta_force;
}
