#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "primitive.h"

class Circle : public Primitive {
    public: 
        Circle(const Point& point, const float radius);
        virtual ~Circle();
        
        const float get_radius() const;  
        
    public:
        float radius_;
};

#endif
