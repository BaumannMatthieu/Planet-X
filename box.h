#ifndef __BOX_H__
#define __BOX_H__

#include "rectangle.h"

class Box {
    public: 
        Box(const Rectangle& rectangle);
        virtual ~Box();
        
        const Rectangle& get_box_rect() const;
        const Point& get_position() const;  
        
    public:
        Rectangle rect_;
        Point center_mass_;
};

#endif
