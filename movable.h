#ifndef __MOVABLE_H__
#define __MOVABLE_H__

#include "vector2.h"
#include "primitive.h"

class Movable {
    public:
       	virtual void move() = 0;
        
        inline const Vector2<float> compute_seek_force(const Point& source, const Point& destination) const;
        inline const Vector2<float> compute_arrive_force(const Point& source, const Point& destination) const; 
        inline const Vector2<float> compute_flee_force(const Point& source, const Point& destination) const;
        inline const Vector2<float> compute_circular_displacement_force(const Point& source, const Point& destination) const;

    protected:
		Vector2<float> force_;
		Vector2<float> acceleration_;
		Vector2<float> velocity_;
        float max_velocity_;
        float max_force_;
		
		float mass_;
};

#endif
