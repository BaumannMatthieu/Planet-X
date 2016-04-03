#ifndef __VERTICE_H__
#define __VERTICE_H__

#include "rectangle.h"

class Vertice {
    public:
        Vertice(const Point& point);
        virtual ~Vertice();
    
        const Point& get_position() const;
        
    public:
        Point center_mass_;
};

#endif
