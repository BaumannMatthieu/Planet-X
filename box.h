#ifndef __BOX_H__
#define __BOX_H__

#include "collisable.h"
#include "rectangle.h"

class Box : public Collisable {
    public: 
        Box(const Rectangle& rectangle);
        virtual ~Box();
        
        const Rectangle& get_box_rect() const;
        const Point& get_position() const;  
        
        virtual bool compute(const Rectangle& rect) const;

    protected:
        Rectangle rect_;
        Point center_mass_;
};

#endif
