#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "primitive.h"

class Circle {
    public: 
        Circle(const Point& point, const float radius);
        virtual ~Circle();
        
        const Point& get_position() const;  
        const float get_radius() const;  
        
    public:
        Point center_mass_;
        float radius_;
};

#endif
